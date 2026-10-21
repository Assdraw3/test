#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <queue>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

// 机床数据结构体
struct MachineData {
    string machine_id;     // 6位设备ID，如"CNC001"
    double temperature;    // 主轴温度（℃）
    double vibration;      // 振动加速度（m/s²）
    string timestamp;      // 格式: "YYYY-MM-DD HH:MM:SS"
    MachineData* next;     // 下一个节点指针

    MachineData(string id, double temp, double vib, string time)
        : machine_id(id), temperature(temp), vibration(vib), timestamp(time), next(nullptr) {
    }
};

// 实时数据缓存队列（基于链表实现）
class DataCacheQueue {
private:
    MachineData* head;          // 队列头
    MachineData* tail;          // 队列尾  
    int max_size;              // 最大缓存条数（2分钟数据）
    int current_size;          // 当前数据条数

public:
    DataCacheQueue(int maxSize = 120000) : head(nullptr), tail(nullptr), max_size(maxSize), current_size(0) {}

    // 数据入队（尾插法）
    bool enqueue(string id, double temp, double vib, string time) {
        // 创建新节点
        MachineData* newData = new MachineData(id, temp, vib, time);

        if (head == nullptr) {
            head = tail = newData;
        }
        else {
            tail->next = newData;
            tail = newData;
        }
        current_size++;

        // 检查是否超过最大缓存，超过则出队最旧数据并持久化
        while (current_size > max_size && head != nullptr) {
            MachineData* oldest = head;
            head = head->next;
            saveToHistory(oldest);
            delete oldest;
            current_size--;
        }

        return true;
    }

    // 按设备ID查询最新数据（从尾部向前查找，提高效率）
    MachineData* findLatestByMachineId(string targetId) {
        // 由于是单向链表，只能从头遍历，但实际中最新数据在尾部附近
        MachineData* current = head;
        MachineData* latestMatch = nullptr;

        // 记录查找时间开始
        clock_t start = clock();

        while (current != nullptr) {
            if (current->machine_id == targetId) {
                latestMatch = current; // 找到就更新，最后找到的就是最新的
            }
            current = current->next;
        }

        // 检查查询延迟
        clock_t end = clock();
        double query_time = double(end - start) / CLOCKS_PER_SEC * 1000; // 毫秒
        if (query_time > 50) {
            cout << "警告：查询延迟 " << query_time << "ms 超过50ms限制" << endl;
        }

        return latestMatch;
    }

    // 获取当前缓存数据量
    int getCurrentSize() {
        return current_size;
    }

    // 手动持久化所有数据并清空缓存
    void manualSaveAll() {
        int savedCount = 0;
        MachineData* current = head;

        while (current != nullptr) {
            saveToHistory(current);
            MachineData* temp = current;
            current = current->next;
            delete temp;
            savedCount++;
        }

        head = tail = nullptr;
        current_size = 0;
        cout << "手动持久化完成，共保存 " << savedCount << " 条数据" << endl;
    }

private:
    // 保存单条数据到历史文件
    void saveToHistory(MachineData* data) {
        if (data == nullptr) return;

        string filename = data->machine_id + "_history.txt";
        ofstream outFile(filename, ios::app);

        if (outFile.is_open()) {
            outFile << data->machine_id << ","
                << fixed << setprecision(1) << data->temperature << ","
                << fixed << setprecision(1) << data->vibration << ","
                << data->timestamp << endl;
            outFile.close();
        }
    }

public:
    // 析构函数，释放内存
    ~DataCacheQueue() {
        MachineData* current = head;
        while (current != nullptr) {
            MachineData* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

// 全局数据缓存实例
DataCacheQueue dataCache;

// 生成当前时间戳
string getCurrentTimestamp() {
    time_t now = time(0);
    tm* localTime = localtime(&now);

    stringstream ss;
    ss << localTime->tm_year + 1900 << "-"
        << setw(2) << setfill('0') << localTime->tm_mon + 1 << "-"
        << setw(2) << setfill('0') << localTime->tm_mday << " "
        << setw(2) << setfill('0') << localTime->tm_hour << ":"
        << setw(2) << setfill('0') << localTime->tm_min << ":"
        << setw(2) << setfill('0') << localTime->tm_sec;

    return ss.str();
}

// 生成设备ID（6位格式）
string generateMachineId(int index) {
    stringstream ss;
    ss << "CNC" << setw(3) << setfill('0') << index;
    return ss.str();
}

// 模拟数据帧解析（简化版）
bool parseDataFrame(string& machineId, double& temp, double& vib, string& timestamp) {
    // 简化的数据帧解析，实际中会解析二进制帧
    // 这里模拟10%的概率数据为空（传感器松动）
    if (rand() % 10 == 0) {
        return false; // 数据为空，过滤
    }

    // 生成正常范围数据
    temp = 35 + (rand() % 26) + (rand() % 10) / 10.0; // 35.0-60.9℃
    vib = 0.1 + (rand() % 20) / 10.0; // 0.1-2.0 m/s²，保留1位小数

    return true;
}

// 模拟生成传感器数据（高频采集）
void generateMachineData(int durationSeconds) {
    cout << "开始模拟 " << durationSeconds << " 秒的数据采集..." << endl;

    int totalGenerated = 0;
    int validData = 0;
    int invalidData = 0;

    for (int sec = 0; sec < durationSeconds; sec++) {
        for (int machineIndex = 1; machineIndex <= 100; machineIndex++) {
            // 每秒每台设备生成10条数据
            for (int i = 0; i < 10; i++) {
                totalGenerated++;

                string machineId = generateMachineId(machineIndex);
                double temperature, vibration;
                string timestamp = getCurrentTimestamp();

                // 解析数据帧
                if (parseDataFrame(machineId, temperature, vibration, timestamp)) {
                    // 有效数据入队
                    dataCache.enqueue(machineId, temperature, vibration, timestamp);
                    validData++;
                }
                else {
                    invalidData++;
                }
            }
        }

        // 模拟1秒时间间隔
        // sleep(1); // 实际运行时取消注释
    }

    cout << "数据生成完成！总生成：" << totalGenerated
        << "条，有效数据：" << validData
        << "条，无效数据：" << invalidData << "条" << endl;
    cout << "当前缓存数据量：" << dataCache.getCurrentSize() << "条" << endl;
}

// 按设备ID查询最新实时数据
void queryLatestDataByMachineId() {
    string targetId;
    cout << "请输入设备ID（格式如CNC001）: ";
    cin >> targetId;

    // 验证ID格式
    if (targetId.length() != 6 || targetId.substr(0, 3) != "CNC") {
        cout << "设备ID格式错误！" << endl;
        return;
    }

    MachineData* result = dataCache.findLatestByMachineId(targetId);

    if (result != nullptr) {
        cout << "找到最新数据 - 设备ID: " << result->machine_id << endl;
        cout << "  主轴温度: " << fixed << setprecision(1) << result->temperature << "℃" << endl;
        cout << "  振动加速度: " << fixed << setprecision(1) << result->vibration << "m/s²" << endl;
        cout << "  时间: " << result->timestamp << endl;

        // 简单异常检测
        if (result->temperature < 35 || result->temperature > 60) {
            cout << "警告：主轴温度异常！" << endl;
        }
        if (result->vibration < 0.1 || result->vibration > 2.0) {
            cout << "警告：振动加速度异常！" << endl;
        }
    }
    else {
        cout << "未找到设备 " << targetId << " 的实时数据" << endl;
    }
}

// 按设备ID+日期+参数类型查询历史数据
void queryHistoryData() {
    string targetId, targetDate, paramType;
    cout << "请输入设备ID（格式如CNC001）: ";
    cin >> targetId;
    cout << "请输入查询日期（格式YYYY-MM-DD）: ";
    cin >> targetDate;
    cout << "请输入参数类型(1:温度 2:振动 3:全部): ";
    cin >> paramType;

    // 验证输入格式
    if (targetDate.length() != 10 || targetDate[4] != '-' || targetDate[7] != '-') {
        cout << "日期格式错误！" << endl;
        return;
    }

    string filename = targetId + "_history.txt";
    ifstream inFile(filename);

    if (!inFile.is_open()) {
        cout << "未找到设备 " << targetId << " 的历史数据文件" << endl;
        return;
    }

    string line;
    vector<string> matchedData;
    int totalCount = 0;

    clock_t start = clock();

    while (getline(inFile, line)) {
        totalCount++;
        // 检查日期匹配
        if (line.length() >= 19) {
            string dataDate = line.substr(line.length() - 19, 10);
            if (dataDate == targetDate) {
                // 检查参数类型
                if (paramType == "1" || paramType == "3") { // 温度或全部
                    matchedData.push_back("温度数据: " + line);
                }
                if (paramType == "2" || paramType == "3") { // 振动或全部
                    matchedData.push_back("振动数据: " + line);
                }
            }
        }
    }

    inFile.close();

    clock_t end = clock();
    double query_time = double(end - start) / CLOCKS_PER_SEC * 1000;

    if (!matchedData.empty()) {
        cout << "找到 " << matchedData.size() << " 条匹配的历史数据（查询耗时: "
            << fixed << setprecision(2) << query_time << "ms）:" << endl;

        // 限制显示条数，避免输出过多
        int displayCount = min(10, (int)matchedData.size());
        for (int i = 0; i < displayCount; i++) {
            cout << matchedData[i] << endl;
        }
        if (matchedData.size() > 10) {
            cout << "...（仅显示前10条，共" << matchedData.size() << "条）" << endl;
        }

        // 检查查询响应时间
        if (query_time > 300) {
            cout << "警告：历史查询响应时间 " << query_time << "ms 超过300ms限制" << endl;
        }
    }
    else {
        cout << "未找到匹配的历史数据" << endl;
    }
}

// 查询缓存数据数量
void showCacheStatus() {
    int count = dataCache.getCurrentSize();
    cout << "当前实时缓存数据数量：" << count << " 条" << endl;
    cout << "缓存容量：最多缓存2分钟数据（约120,000条）" << endl;
    if (count > 100000) {
        cout << "提示：缓存数据量较大，建议及时持久化" << endl;
    }
}

void showMenu() {
    cout << "\n========= 精密数控机床监测平台 =========\n";
    cout << "1. 模拟生成机床数据（指定时长-秒）\n";
    cout << "2. 按设备ID查询最新实时数据\n";
    cout << "3. 按设备ID+日期+参数类型查询历史数据\n";
    cout << "4. 查询当前实时缓存数据状态\n";
    cout << "5. 手动持久化所有缓存数据\n";
    cout << "0. 退出系统\n";
    cout << "======================================\n";
    cout << "请选择操作：";
}

//// 测试用例函数
//void runTestCases() {
//    cout << "\n=== 开始功能测试 ===" << endl;
//
//    // 测试用例1：查询存在的设备数据
//    cout << "\n测试用例1：查询存在的设备数据" << endl;
//    dataCache.enqueue("CNC001", 45.5, 1.2, "2024-01-01 10:00:00");
//    MachineData* result1 = dataCache.findLatestByMachineId("CNC001");
//    if (result1 != nullptr) {
//        cout << "✓ 测试通过：成功查询到存在的设备数据" << endl;
//    }
//    else {
//        cout << "✗ 测试失败：未查询到存在的设备数据" << endl;
//    }
//
//    // 测试用例2：查询不存在的设备数据
//    cout << "\n测试用例2：查询不存在的设备数据" << endl;
//    MachineData* result2 = dataCache.findLatestByMachineId("CNC999");
//    if (result2 == nullptr) {
//        cout << "✓ 测试通过：正确返回空值" << endl;
//    }
//    else {
//        cout << "✗ 测试失败：应返回空值" << endl;
//    }
//
//    // 测试用例3：过滤空值数据
//    cout << "\n测试用例3：验证空值数据过滤" << endl;
//    int beforeSize = dataCache.getCurrentSize();
//    // 模拟空值数据（parseDataFrame返回false的情况）
//    // 这里通过直接调用enqueue来模拟，实际中空值数据不会调用enqueue
//    cout << "✓ 测试通过：空值数据已在生成阶段过滤" << endl;
//
//    // 测试用例4：历史数据查询
//    cout << "\n测试用例4：准备历史数据文件" << endl;
//    ofstream testFile("CNC001_history.txt");
//    if (testFile.is_open()) {
//        testFile << "CNC001,45.5,1.2,2024-01-01 10:00:00" << endl;
//        testFile << "CNC001,46.0,1.3,2024-01-01 10:00:01" << endl;
//        testFile.close();
//        cout << "✓ 测试文件创建完成" << endl;
//    }
//
//    cout << "\n=== 功能测试完成 ===" << endl;
//}

int main() {
    srand(time(0)); // 初始化随机种子

    int choice;
    bool running = true;

    cout << "=== 精密数控机床监测平台后端数据管理核心程序 ===" << endl;
    cout << "系统初始化完成，开始运行..." << endl;

    // 运行测试用例
    //runTestCases();

    while (running) {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            int duration;
            cout << "请输入模拟数据采集时长（秒）: ";
            cin >> duration;
            if (duration > 0) {
                generateMachineData(duration);
            }
            else {
                cout << "时长必须大于0" << endl;
            }
            break;
        }
        case 2:
            queryLatestDataByMachineId();
            break;
        case 3:
            queryHistoryData();
            break;
        case 4:
            showCacheStatus();
            break;
        case 5:
            dataCache.manualSaveAll();
            break;
        case 0:
            cout << "感谢使用精密数控机床监测平台！" << endl;
            running = false;
            break;
        default:
            cout << "无效选择，请重新输入！" << endl;
            break;
        }
    }

    return 0;
}