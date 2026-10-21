精密数控机床监测平台1. 函数模块说明
结构体定义
SensorDataNode（传感器数据节点）
typedef struct SensorDataNode {
    char machine_id[7];        // 设备ID（6位字符+结束符）
    double temperature;        // 主轴温度值（℃）
    double vibration;         // 振动加速度值（m/s²）
    char timestamp[20];       // 时间戳（YYYY-MM-DD HH:MM:SS）
    struct SensorDataNode* next;  // 指向下一个节点的指针
} SensorDataNode;
字段含义：
machine_id：唯一设备标识符，格式为"CNC001"~"CNC100"
temperature：主轴温度测量值，范围35.0-60.0℃，保留1位小数
vibration：振动加速度测量值，范围0.1-2.0m/s²，保留1位小数
timestamp：数据采集时间，精确到秒
next：链表下一个节点指针，实现线性数据结构
DeviceDataList（设备链表管理结构）
typedef struct {
    SensorDataNode* head;      // 链表头指针
    SensorDataNode* tail;      // 链表尾指针（优化尾插效率）
    int node_count;           // 当前节点数量
    int max_capacity;         // 最大缓存容量（2分钟数据量）
} DeviceDataList;
字段含义：
head：指向链表第一个数据节点的指针
tail：指向链表最后一个数据节点的指针，用于快速尾插
node_count：当前链表中有效数据节点数量
max_capacity：链表最大容量，根据2分钟数据量设定
核心函数说明
（1）节点创建函数 create_data_node
SensorDataNode* create_data_node(const char* timestamp, double temp, double vib, const char* machine_id);
功能：动态创建新的传感器数据节点并初始化数据字段
入参：
timestamp：数据时间戳字符串
temp：温度测量值
vib：振动加速度测量值
machine_id：设备标识符
返回值：成功返回节点指针，失败返回NULL
设计思路：使用malloc动态分配内存，进行参数校验和数据拷贝
（2）节点插入函数 insert_node_to_tail
int insert_node_to_tail(const char* machine_id, SensorDataNode* new_node);
功能：使用尾插法将新节点插入到指定设备链表的尾部
入参：
machine_id：目标设备ID
new_node：待插入的新节点指针
返回值：成功返回0，失败返回-1
注意事项：
维护尾指针tail确保O(1)时间复杂度的插入操作
自动更新节点计数器node_count
检查链表容量，超限时触发过期数据清理
（3）过期节点清理函数 remove_expired_nodes
void remove_expired_nodes(const char* machine_id, const char* expire_timestamp);
功能：删除指定设备链表中超过2分钟有效期的数据节点
入参：
machine_id：目标设备ID
expire_timestamp：过期时间戳界限值
内存释放逻辑：
遍历链表，比较节点时间戳与过期界限
释放过期节点的内存资源
维护链表头尾指针的连续性
更新节点计数器统计信息
（4）最新数据查询函数 query_latest_data
SensorDataNode* query_latest_data(const char* machine_id);
功能：查询指定设备的最新采集数据（时间戳最新的节点）
入参：machine_id- 目标设备标识符
返回值：找到返回节点指针，未找到返回NULL
算法优化：直接从链表尾部开始反向查找，提高查询效率
（5）链表销毁函数 destroy_device_list
void destroy_device_list(const char* machine_id);
功能：释放指定设备链表的所有节点内存资源
入参：machine_id- 目标设备标识符
内存管理：遍历整个链表，逐个释放节点内存，避免内存泄漏
2. 运行说明
运行环境要求
操作系统：Linux（Ubuntu 20.04+/CentOS 7+）或 Windows 10/11
编译器：GCC 9.4.0+ 或 MinGW-w64（Windows）
C标准：C11及以上标准支持
依赖库
无第三方库依赖
仅使用C标准库：
stdio.h：标准输入输出
stdlib.h：内存分配和系统函数
time.h：时间处理功能
string.h：字符串操作
ctype.h：字符类型判断
编译指令
# Linux/Unix 系统编译指令
gcc -std=c11 -o machine_monitor main.c data_manager.c linked_list.c -Wall -O2

# Windows 系统编译指令（MinGW）
gcc -std=c11 -o machine_monitor.exe main.c data_manager.c linked_list.c -Wall
文件说明：
main.c：主程序文件，包含用户界面和菜单逻辑
data_manager.c：数据管理核心模块，实现业务逻辑
linked_list.c：链表操作实现文件，包含所有数据结构操作函数
运行步骤
编译程序：
gcc -std=c11 -o machine_monitor main.c data_manager.c linked_list.c -Wall
执行程序：
# Linux/Unix 系统
./machine_monitor

# Windows 系统
machine_monitor.exe
系统初始化：程序启动后自动初始化100个设备的链表结构
3. 测试指令
基础功能测试
测试1：最新数据查询验证
测试指令：
请输入操作选择：2
请输入设备ID：CNC001
预期输出：
找到设备CNC001的最新数据：
温度：45.5℃ 振动：1.2m/s² 时间：2024-01-01 10:30:45
验证要点：
输出包含正确的设备ID、温度、振动值和时间戳
查询响应时间应在50ms以内
数据显示格式符合规范（保留1位小数）
测试2：不存在的设备查询
测试指令：
请输入操作选择：2
请输入设备ID：CNC999
预期输出：
未找到设备CNC999的实时数据
验证要点：
系统正确处理不存在的设备ID
返回明确的错误提示信息
程序不发生崩溃或异常
边界条件测试
测试3：链表容量边界测试
测试步骤：
模拟生成3分钟的高频数据（每秒10条）
执行查询指令：
请输入操作选择：2
请输入设备ID：CNC050
验证要点：
系统自动清理超过2分钟的过期数据
链表节点数量维持在合理范围内（约12,000条）
查询功能在数据量大的情况下仍能快速响应
测试4：数据持久化测试
测试指令：
请输入操作选择：5
预期输出：
开始持久化数据...
设备CNC001保存125条数据
设备CNC002保存118条数据
...
持久化完成，共保存12580条数据
验证要点：
数据正确写入对应的历史文件（CNC001_history.txt等）
文件格式符合规范：设备ID,温度,振动,时间戳
持久化过程不影响实时数据采集
性能测试指令
测试5：查询性能验证
测试方法：连续执行多次查询操作，观察响应时间
# 批量测试脚本示例（Linux）
for i in {1..10}; do
    echo "2" | ./machine_monitor  # 自动选择查询功能
    echo "CNC0$(printf "%02d" $((i%100+1)))"  # 循环查询不同设备
done
性能要求：
实时数据查询：≤50ms
历史数据查询：≤300ms
内存使用：稳定在合理范围内
异常处理测试
测试6：空值数据过滤
验证方法：观察数据生成过程中的过滤日志
预期结果：系统自动识别并过滤data_value为空的无效数据
测试7：文件操作异常
测试方法：手动删除历史文件后执行查询操作
预期结果：系统优雅处理文件不存在的情况，给出友好提示
备注：以上测试指令需在程序正常运行状态下执行，确保系统已正确初始化所有设备链表结构