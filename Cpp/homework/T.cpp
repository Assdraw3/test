#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
using namespace std;

class StInfo
{

private:
    int ID;
    char name[20];
    char classname[20];
    char phonenumber[20];
public:
    int get_ID()
    {
        return ID;
    }
    char* get_name()
    {
        return name;
    }
    char* get_classname()
    {
        return classname;
    }
    char* get_phonenumber()
    {
        return phonenumber;
    }
    void set_ID(int n)
    {
        ID = n;
    }
    void set_name(char* n)
    {
        strcpy(name, n);
    }
    void set_classname(char* n)
    {
        strcpy(classname, n);
    }
    void set_phonenumber(char* n)
    {
        strcpy(phonenumber, n);
    }

};

int main()
{
    int Id;
    char Name[20] = { 0 };
    char ClassName[20] = { 0 };
    char PhoneNumber[20] = { 0 };
    cin >> Id >> Name >> ClassName >> PhoneNumber;
    StInfo std1;
    std1.set_ID(Id);
    std1.set_name(Name);
    std1.set_classname(ClassName);
    std1.set_phonenumber(PhoneNumber);
    cout << "学号：" << std1.get_ID() << endl;
    cout << "姓名：" << std1.get_name() << endl;
    cout << "班级：" << std1.get_classname() << endl;
    cout << "手机号：" << std1.get_phonenumber() << endl;
    return 0;
}

