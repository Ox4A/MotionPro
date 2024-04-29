#include<chrono>
#include<thread>
#include<iostream>
#include<sstream>
#include"DynamicPassword.h"
using namespace std;
string Padding(uint32_t P) {
    stringstream ss;
    ss << P;
    string numStr;
    string res = "000000";
    ss >> numStr;  //若res=23 应变为000023
    for (int i = 6 - numStr.size(); i < 6; i++) {
        res[i]=numStr[i - (6 - numStr.size())];
    }
    return res;
}

void DynamicPasswdVerify() {
    uint32_t P;
    string verify_passwd;
    string standard_passwd;
    cout << "==================MotionPro服务器=====================" << endl;
    string user_name;
    cout << "请输入你的用户名：";
    cin >> user_name;
    P = GenerateDynamicPassword(user_name);
    standard_passwd = Padding(P);
    cout << "请输入你的动态口令：";
    cin >> verify_passwd;
    while (true) {
        if (verify_passwd == standard_passwd) {
            cout << "验证通过，欢迎进入交大VPN" << endl;
            break;
        }
        else {
            cout << "验证失败，请重新输入动态口令：";
            cin >> verify_passwd;
            P = GenerateDynamicPassword(user_name);
            standard_passwd = Padding(P);
        }
    }
}