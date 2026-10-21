//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <ctime>
//#include <iomanip>
//#include <vector>
//#include <sstream>
//
//using namespace std;
//
//// 传感器数据结构体
//struct SensorData {
//    string sensor_id;    // 6位传感器ID，如"AGR001"
//    int data_type;       // 0:室温, 1:湿度
//    int data_value;      // 温度:-10~45; 湿度:0~100; -1表示空值
//    string timestamp;    // 格式: "YYYY-MM-DD HH:MM:SS"
//    SensorData* next;    // 下一个节点指针
//
//    SensorData(string id, int type, int value, string time)
//        : sensor_id(id), data_type(type), data_value(value), timestamp(time), next(nullptr) {
//    }
//};
//
//// 单链表类
//class SensorLinkedList {
//private:
//    SensorData* head;     // 链表头节点
//    SensorData* tail;     // 链表尾节点
//    int length;          // 链表长度
//
//public:
//    SensorLinkedList() : head(nullptr), tail(nullptr), length(0) {}
//
//    // 尾插法插入数据
//    void insertData(string id, int type, int value, string time) {
//        SensorData* newData = new SensorData(id, type, value, time);
//
//        if (head == nullptr) {
//            head = tail = newData;
//        }
//        else {
//            tail->next = newData;
//            tail = newData;
//        }
//        length++;
//
//        // 检查缓存条数提示
//        if (length > 1000) {
//            cout << "警告：缓存接近上限，当前数据条数：" << length << endl;
//        }
//    }
//
//    // 按ID查询最新数据
//    SensorData* findLatestById(string targetId) {
//        SensorData* current = head;
//        SensorData* latestMatch = nullptr;
//
//        while (current != nullptr) {
//            if (current->sensor_id == targetId) {
//                latestMatch = current;
//            }
//            current = current->next;
//        }
//
//        return latestMatch;
//    }
//
//    // 获取链表长度
//    int getLength() {
//        return length;
//    }
//
//    // 清空链表并将数据存入历史文件
//    void clearAndSaveToHistory() {
//        if (head == nullptr) {
//            cout << "缓存为空，无需存储" << endl;
//            return;
//        }
//
//        SensorData* current = head;
//        int savedCount = 0;
//
//        while (current != nullptr) {
//            // 按传感器ID生成文件名
//            string filename = current->sensor_id + "_history.txt";
//            ofstream outFile(filename, ios::app); // 追加模式
//
//            if (!outFile.is_open()) {
//                cout << "打开文件 " << filename << " 失败" << endl;
//                current = current->next;
//                continue;
//            }
//
//            // 写入数据：ID,类型,值,时间戳
//            outFile << current->sensor_id << ","
//                << current->data_type << ","
//                << current->data_value << ","
//                << current->timestamp << endl;
//
//            outFile.close();
//            savedCount++;
//
//            SensorData* temp = current;
//            current = current->next;
//            delete temp; // 释放内存
//        }
//
//        head = tail = nullptr;
//        length = 0;
//
//        cout << "历史数据存储完成，共保存 " << savedCount << " 条数据" << endl;
//    }
//
//    // 析构函数，释放所有节点内存
//    ~SensorLinkedList() {
//        SensorData* current = head;
//        while (current != nullptr) {
//            SensorData* temp = current;
//            current = current->next;
//            delete temp;
//        }
//    }
//};
//
//// 全局链表实例
//SensorLinkedList sensorCache;
//
//// 生成当前时间戳
//string getCurrentTimestamp() {
//    time_t now = time(0);
//    tm* localTime = localtime(&now);
//
//    stringstream ss;
//    ss << localTime->tm_year + 1900 << "-"
//        << setw(2) << setfill('0') << localTime->tm_mon + 1 << "-"
//        << setw(2) << setfill('0') << localTime->tm_mday << " "
//        << setw(2) << setfill('0') << localTime->tm_hour << ":"
//        << setw(2) << setfill('0') << localTime->tm_min << ":"
//        << setw(2) << setfill('0') << localTime->tm_sec;
//
//    return ss.str();
//}
//
//// 生成传感器ID（6位格式）
//string generateSensorId(int index) {
//    stringstream ss;
//    ss << "AGR" << setw(3) << setfill('0') << index;
//    return ss.str();
//}
//
//// 模拟生成传感器数据
//void generateSensorData(int count) {
//    int validCount = 0;
//    int invalidCount = 0;
//
//    for (int i = 0; i < count; i++) {
//        // 随机生成传感器索引（1-1000）
//        int sensorIndex = i;
//        string sensorId = generateSensorId(sensorIndex);
//
//        // 随机生成数据类型（0或1）
//        int dataType = rand() % 2;
//
//        // 随机生成数据值（有10%概率生成空值-1）
//        int dataValue;
//        if (rand() % 10 == 0) { // 10%概率生成空值
//            dataValue = -1;
//            invalidCount++;
//        }
//        else {
//            if (dataType == 0) { // 温度：-10~45
//                dataValue = rand() % 56 - 10;
//            }
//            else { // 湿度：0~100
//                dataValue = rand() % 101;
//            }
//            validCount++;
//        }
//
//        string timestamp = getCurrentTimestamp();
//
//        // 过滤空值数据
//        if (dataValue == -1) {
//            cout << "空值数据，过滤 - ID: " << sensorId
//                << ", 类型: " << dataType
//                << ", 值: " << dataValue << endl;
//        }
//        else {
//            // 有效数据插入缓存
//            sensorCache.insertData(sensorId, dataType, dataValue, timestamp);
//        }
//
//        // 模拟数据处理延迟
//        // this_thread::sleep_for(chrono::milliseconds(1));
//    }
//
//    cout << "数据生成完成！有效数据：" << validCount
//        << "条，无效数据：" << invalidCount << "条" << endl;
//}
//
//// 按ID查询最新实时数据
//void queryLatestDataById() {
//    string targetId;
//    cout << "请输入传感器ID（格式如AGR001）: ";
//    cin >> targetId;
//
//    // 验证ID格式
//    if (targetId.length() != 6 || targetId.substr(0, 3) != "AGR") {
//        cout << "传感器ID格式错误！" << endl;
//        return;
//    }
//
//    SensorData* result = sensorCache.findLatestById(targetId);
//
//    if (result != nullptr) {
//        string typeStr = (result->data_type == 0) ? "室温" : "湿度";
//        string unit = (result->data_type == 0) ? "℃" : "%";
//
//        cout << "找到最新数据 - ID: " << result->sensor_id
//            << ", 类型: " << typeStr
//            << ", 值: " << result->data_value << unit
//            << ", 时间: " << result->timestamp << endl;
//    }
//    else {
//        cout << "未找到传感器 " << targetId << " 的实时数据" << endl;
//    }
//}
//
//// 按ID+日期查询历史数据
//void queryHistoryDataByIdAndDate() {
//    string targetId, targetDate;
//    cout << "请输入传感器ID（格式如AGR001）: ";
//    cin >> targetId;
//    cout << "请输入查询日期（格式YYYY-MM-DD）: ";
//    cin >> targetDate;
//
//    // 验证日期格式（简化验证）
//    if (targetDate.length() != 10 || targetDate[4] != '-' || targetDate[7] != '-') {
//        cout << "日期格式错误！" << endl;
//        return;
//    }
//
//    string filename = targetId + "_history.txt";
//    ifstream inFile(filename);
//
//    if (!inFile.is_open()) {
//        cout << "未找到传感器 " << targetId << " 的历史数据文件" << endl;
//        return;
//    }
//
//    string line;
//    vector<string> matchedData;
//    int totalCount = 0;
//
//    while (getline(inFile, line)) {
//        totalCount++;
//        // 从数据行中提取日期部分（前10个字符）
//        if (line.length() >= 10) {
//            string dataDate = line.substr(line.length() - 19, 10); // 提取日期部分
//            if (dataDate == targetDate) {
//                matchedData.push_back(line);
//            }
//        }
//    }
//
//    inFile.close();
//
//    if (!matchedData.empty()) {
//        cout << "找到 " << matchedData.size() << " 条匹配的历史数据：" << endl;
//        for (const string& data : matchedData) {
//            cout << data << endl;
//        }
//        cout << "共找到 " << matchedData.size() << " 条历史数据（总共扫描 " << totalCount << " 条）" << endl;
//    }
//    else {
//        cout << "未找到传感器 " << targetId << " 在日期 " << targetDate << " 的历史数据" << endl;
//    }
//}
//
//// 查询当前缓存数据数量
//void showCacheCount() {
//    int count = sensorCache.getLength();
//    cout << "当前实时缓存数据数量：" << count << " 条" << endl;
//    if (count > 1000) {
//        cout << "警告：缓存接近上限！" << endl;
//    }
//}
//
//// 手动存入历史文件并清空缓存
//void manualSaveToHistory() {
//    cout << "开始手动存储历史数据..." << endl;
//    sensorCache.clearAndSaveToHistory();
//}
//
//void showMenu() {
//    cout << "\n========= 智能农业监测平台 =========\n";
//    cout << "1. 模拟生成传感器数据（指定数量）\n";
//    cout << "2. 按ID查询最新实时数据\n";
//    cout << "3. 按ID+日期查询历史数据\n";
//    cout << "4. 查询当前实时缓存数据数量\n";
//    cout << "5. 手动存入历史文件并清空缓存\n";
//    cout << "0. 退出系统\n";
//    cout << "==================================\n";
//    cout << "请选择操作：";
//}
//
//int main() {
//    srand(time(0)); // 初始化随机种子
//
//    int choice;
//    bool running = true;
//
//    cout << "=== 智能农业监测平台后端数据管理核心程序 ===" << endl;
//    cout << "系统初始化完成，开始运行..." << endl;
//
//    while (running) {
//        showMenu();
//        cin >> choice;
//
//        switch (choice) {
//        case 1: {
//            int count;
//            cout << "请输入要生成的数据条数：";
//            cin >> count;
//            generateSensorData(count);
//            break;
//        }
//        case 2:
//            queryLatestDataById();
//            break;
//        case 3:
//            queryHistoryDataByIdAndDate();
//            break;
//        case 4:
//            showCacheCount();
//            break;
//        case 5:
//            manualSaveToHistory();
//            break;
//        case 0:
//            cout << "感谢使用智能农业监测平台！" << endl;
//            running = false;
//            break;
//        default:
//            cout << "无效选择，请重新输入！" << endl;
//            break;
//        }
//    }
//
//    return 0;
//}