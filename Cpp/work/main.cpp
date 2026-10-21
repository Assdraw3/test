//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <iostream>
//#include <string>
//#include <fstream>
//#include <vector>
//#include <map>
//#include <stdbool.h>
//using namespace std;
//
//
//class User {
//private:
//	string username;
//	string password;
//	double money;
//	map<string, int> holdings;
//public:
//	User()
//	{
//		money = 10000;
//	}
//	void saveUserToFile() {
//		ofstream file;
//		file.open("UserDate.txt", ios::app);
//		file << username << " " << password << " " << money << endl;
//		file.close();
//	}
//	void register_user()
//	{
//		ifstream file;
//		file.open("UserDate.txt");
//		while(1)
//		{
//			cout << "请创建用户名:\n";
//			cin >> username;
//			string line;
//			bool flag = true;
//			while (getline(file, line))
//			{
//				if (line.find(username) != string::npos)
//				{
//					flag = 0;
//					break;
//				}
//			}
//			if (flag)
//			{
//				cout << "请设置密码：\n";
//				cin >> password;
//				saveUserToFile();
//				break;
//			}
//			else
//			{
//				cout << "该用户名已经被使用\n";
//			}
//		}
//		file.close();
//	}
//	bool login()
//	{
//		string tName;
//		string tPassword;
//		cout << "请输入用户名:\n";
//		cin >> tName;
//		cout << "请输入密码：\n";
//		cin >> tPassword;
//		ifstream file;
//		file.open("UserDate.txt");
//		        string line;
//		        while (getline(file, line)) {
//		            if (line.find(tName) != string::npos && line.find(tPassword) != string::npos) {
//		                username = tName;
//		                password = tPassword;
//		                cout << "登录成功！" << endl;
//						file.close();
//		                return true;
//		            }
//		        }
//		        cout << "用户名或密码错误！请重新输入" << endl;
//				file.close();
//		        return false;
//	}
//	void show_message()
//	{
//		cout << username << endl;
//		cout << password << endl;
//	}
//	void buyStock(string stockCode, int quantity, double price) {
//		double totalCost = price * quantity;
//		if (money >= totalCost) {
//			money -= totalCost;
//			holdings[stockCode] += quantity;
//			cout << "购买成功！" << endl;
//		}
//		else {
//			cout << "余额不足！" << endl;
//		}
//	}
//
//	void sellStock(string stockCode, int quantity, double price) {
//		if (holdings[stockCode] >= quantity) {
//			holdings[stockCode] -= quantity;
//			money += price * quantity;
//			cout << "卖出成功！" << endl;
//		}
//		else {
//			cout << "持有股票数量不足！" << endl;
//		}
//	}
//
//	void showHoldings() {
//		cout << "当前持仓：" << endl;
//		for (auto& holding : holdings) {
//			cout << "股票代码: " << holding.first << ", 持有数量: " << holding.second << endl;
//		}
//		cout << "账户余额: " << money << "元" << endl;
//	}
//
//};

//class Stock {
//private:
//	string StockName;
//	string StockCode;
//	double price;
//public:
//	Stock(string c, string n, double p)
//	{
//		StockName = c;
//		StockCode = n;
//		price = p;
//	}
//	void loadStocksFromFile() 
//	{   
//		ifstream file("stocks.txt");
//		string line;
//		while (getline(file, line))
//		{
//			cout << line << endl;
//		}
//	}
//	void showStockList()
//	{
//		ifstream file("stocks.txt");
//		string line;
//		while (getline(file, line))
//		{
//			cout << line << endl;
//		}
//	}
//	double getPrice(string stockCode) {
//		ifstream file("stocks.txt");
//		string line;
//		while (getline(file, line)) {
//			if (line.find(stockCode) != string::npos) {
//				size_t pos = line.find_last_of(' ');
//				price = stod(line.substr(pos + 1));
//				return price;
//			}
//		}
//		return 0.0;
//	}
//};
//class Transaction {
//private:
//	string user;
//	string stockCode;
//	int quantity;
//	double price;
//	string type; // "buy" or "sell"
//
//public:
//	void recordTransaction() {
//		ofstream file("transactions.txt", ios::app);
//		file << user << " " << stockCode << " " << quantity << " " << price << " " << type << endl;
//	}
//
//	void loadTransactionsFromFile() {
//		ifstream file("transactions.txt");
//		string line;
//		while (getline(file, line)) {
//			cout << line << endl;
//		}
//	}
//};
//void StockSystem()
//{
//	User user;
//	Stock stock("", "", 0.0);
//	//Transaction transaction;
//
//	int choice;
//	while (true) {
//		cout << "1. 注册\n2. 登录\n3. 查看股票列表\n4. 买入股票\n5. 卖出股票\n6. 查看持仓\n7. 退出\n";
//		cout << "请选择操作: \n";
//		cin >> choice;
//
//		if (choice == 1) {
//			user.register_user();
//		}
//		else if (choice == 2) {
//			if (user.login()) {
//				while (true) {
//					cout << "1. 查看股票列表\n2. 买入股票\n3. 卖出股票\n4. 查看持仓\n5. 退出\n";
//					cout << "请选择操作: ";
//					cin >> choice;
//
//					if (choice == 1) {
//						stock.showStockList();
//					}
//					else if (choice == 2) {
//						string stockCode;
//						int quantity;
//						cout << "请输入股票代码: ";
//						cin >> stockCode;
//						cout << "请输入购买数量: ";
//						cin >> quantity;
//						double price = stock.getPrice(stockCode);
//						user.buyStock(stockCode, quantity, price);
//					}
//					else if (choice == 3) {
//						string stockCode;
//						int quantity;
//						cout << "请输入股票代码: ";
//						cin >> stockCode;
//						cout << "请输入卖出数量: ";
//						cin >> quantity;
//						double price = stock.getPrice(stockCode);
//						user.sellStock(stockCode, quantity, price);
//					}
//					else if (choice == 4) {
//						user.showHoldings();
//					}
//					else if (choice == 5) {
//
//						break;
//					}
//				}
//			}
//		}
//		else if (choice == 3) {
//			stock.showStockList();
//		}
//		else if (choice == 4) {
//			string stockCode;
//			int quantity;
//			cout << "请输入股票代码: ";
//			cin >> stockCode;
//			cout << "请输入购买数量: ";
//			cin >> quantity;
//			double price = stock.getPrice(stockCode);
//			user.buyStock(stockCode, quantity, price);
//		}
//		else if (choice == 5) {
//			string stockCode;
//			int quantity;
//			cout << "请输入股票代码: ";
//			cin >> stockCode;
//			cout << "请输入卖出数量: ";
//			cin >> quantity;
//			double price = stock.getPrice(stockCode);
//			user.sellStock(stockCode, quantity, price);
//		}
//		else if (choice == 6) {
//			user.showHoldings();
//		}
//		else if (choice == 7) {
//			break;
//		}
//	}
//}
//
//int main()
//{
//	StockSystem();
//
//	return 0;
//}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <stdbool.h>
#include <sstream>
#include <iomanip>
using namespace std;

class Transaction {
public:
    void recordTransaction(const string& username, const string& action,
        const string& code, int qty) {
        // 获取当前记录数量作为序号
        static int counter = 0;
        

        // 追加写入记录
        ofstream file("record.txt", ios::app);
        file << ++counter << " "
            << username << " "
            << action << " "
            << code << " "
            << qty << endl;
        file.close();
    }
};

class User {
private:
    string username;
    string password;
    double money;
    map<string, int> holdings;

    void loadHoldingsFromFile() {
        holdings.clear();
        ifstream file("Holding.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string u, stockCode;
            int quantity;
            if (ss >> u >> stockCode >> quantity) {
                if (u == username) {
                    holdings[stockCode] = quantity;
                }
            }
        }
        file.close();
    }

    void saveHoldingsToFile() {
        vector<string> lines;
        ifstream inFile("Holding.txt");
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string u;
            if (ss >> u && u != username) {
                lines.push_back(line);
            }
        }
        inFile.close();

        for (auto& h : holdings) {
            if (h.second > 0) {
                ostringstream oss;
                oss << username << " " << h.first << " " << h.second;
                lines.push_back(oss.str());
            }
        }

        ofstream outFile("Holding.txt");
        for (auto& l : lines) {
            outFile << l << endl;
        }
        outFile.close();
    }

public:
    User() {
        money = 10000;
    }

    void saveUserToFile() {
        ofstream file("UserDate.txt", ios::app);
        file << username << " " << password << " " << fixed << setprecision(2) << money << endl;
        file.close();
    }

    void updateUserInFile() {
        ifstream inFile("UserDate.txt");
        vector<string> lines;
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string u, p;
            double m;
            if (ss >> u >> p >> m) {
                if (u == username && p == password) {
                    ostringstream oss;
                    oss << username << " " << password << " " << fixed << setprecision(2) << money;
                    line = oss.str();
                }
            }
            lines.push_back(line);
        }
        inFile.close();

        ofstream outFile("UserDate.txt");
        for (const auto& l : lines) {
            outFile << l << endl;
        }
        outFile.close();
    }

    void register_user() {
        ifstream file("UserDate.txt");
        while (1) {
            cout << "请创建用户名:\n";
            cin >> username;
            string line;
            bool flag = true;
            while (getline(file, line)) {
                stringstream ss(line);
                string u, p;
                double m;
                if (ss >> u >> p >> m) {
                    if (u == username) {
                        flag = false;
                        break;
                    }
                }
            }
            if (flag) {
                cout << "请设置密码：\n";
                cin >> password;
                saveUserToFile();
                cout << "注册成功\n" << endl;
                break;
            }
            else {
                cout << "该用户名已经被使用\n";
            }
            file.clear();
            file.seekg(0);
        }
        file.close();
    }

    bool login() {
        string tName, tPassword;
        cout << "请输入用户名:\n";
        cin >> tName;
        cout << "请输入密码：\n";
        cin >> tPassword;
        ifstream file("UserDate.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string u, p;
            double m;
            if (ss >> u >> p >> m) {
                if (u == tName && p == tPassword) {
                    username = u;
                    password = p;
                    money = m;
                    loadHoldingsFromFile();
                    cout << "登录成功！" << endl;
                    file.close();
                    return true;
                }
            }
        }
        cout << "用户名或密码错误！请重新输入" << endl;
        file.close();
        return false;
    }

    void buyStock(string stockCode, int quantity, double price) {
        double totalCost = price * quantity;
        if (money >= totalCost) {
            money -= totalCost;
            holdings[stockCode] += quantity;
            cout << "购买成功！" << endl;
            updateUserInFile();
            saveHoldingsToFile();
            Transaction().recordTransaction(username, "买入", stockCode, quantity);
        }
        else {
            cout << "余额不足！" << endl;
        }
    }

    void sellStock(string stockCode, int quantity, double price) {
        if (holdings[stockCode] >= quantity) {
            holdings[stockCode] -= quantity;
            money += price * quantity;
            cout << "卖出成功！" << endl;
            updateUserInFile();
            saveHoldingsToFile();
            Transaction().recordTransaction(username, "卖出", stockCode, quantity);
        }
        else {
            cout << "持有股票数量不足！" << endl;
        }
    }

    void showHoldings() {
        cout << "当前持仓：" << endl;
        for (auto& holding : holdings) {
            if (holding.second > 0) {
                cout << "股票代码: " << holding.first << ", 持有数量: " << holding.second << endl;
            }
        }
        cout << "账户余额: " << fixed << setprecision(2) << money << "元" << endl;
    }
};

class Stock {
private:
    string StockName;
    string StockCode;
    double price;
public:
    Stock(string c, string n, double p) {
        StockName = c;
        StockCode = n;
        price = p;
    }

    void showStockList() {
        ifstream file("stocks.txt");
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
    }

    double getPrice(string stockCode) {
        ifstream file("stocks.txt");
        string line;
        while (getline(file, line)) {
            if (line.find(stockCode) != string::npos) {
                size_t pos = line.find_last_of(' ');
                price = stod(line.substr(pos + 1));
                return price;
            }
        }
        return 0.0;
    }
};

void StockSystem() {
    User GlobalUser;
    Stock stock("", "", 0.0);

    int choice;
    while (true) {
        cout << "\n1. 注册\n2. 登录\n3. 查看股票列表\n4. 退出系统\n";
        cout << "请选择操作: ";
        cin >> choice;

        if (choice == 1) {
            GlobalUser.register_user();
        }
        else if (choice == 2) {
            User CurrentUser;
            if (CurrentUser.login()) {
                int innerChoice;
                while (true) {
                    cout << "\n1. 查看股票列表\n2. 买入股票\n3. 卖出股票\n4. 查看持仓\n5. 退出登录\n";
                    cout << "请选择操作: ";
                    cin >> innerChoice;

                    if (innerChoice == 1) {
                        stock.showStockList();
                    }
                    else if (innerChoice == 2) {
                        string stockCode;
                        int quantity;
                        cout << "请输入股票代码: ";
                        cin >> stockCode;
                        cout << "请输入购买数量: ";
                        cin >> quantity;
                        double price = stock.getPrice(stockCode);
                        CurrentUser.buyStock(stockCode, quantity, price);
                    }
                    else if (innerChoice == 3) {
                        string stockCode;
                        int quantity;
                        cout << "请输入股票代码: ";
                        cin >> stockCode;
                        cout << "请输入卖出数量: ";
                        cin >> quantity;
                        double price = stock.getPrice(stockCode);
                        CurrentUser.sellStock(stockCode, quantity, price);
                    }
                    else if (innerChoice == 4) {
                        CurrentUser.showHoldings();
                    }
                    else if (innerChoice == 5) {
                        CurrentUser = User();
                        break;
                    }
                }
            }
        }
        else if (choice == 3) {
            stock.showStockList();
        }
        else if (choice == 4) {
            break;
        }
    }
}

int main() {
    // 初始化必要文件
    ofstream("Holding.txt").close();
    ofstream("record.txt").close();

    StockSystem();
    return 0;
}
