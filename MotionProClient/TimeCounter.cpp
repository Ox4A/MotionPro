#include<chrono>
#include<thread>
#include<iostream>
#include<sstream>
#include"DynamicPassword.h"
using namespace std;
extern int Tc;
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

void FlushShowPassword() {
    string user_name;
    cout << "==================MotionPro客户端=====================" << endl;
    cout << "请输入你的用户名：";
    cin >> user_name;
    uint32_t P;
    // 记录上一次输出的时间点
    P = GenerateDynamicPassword(user_name);
    auto lastOutputTime = chrono::steady_clock::now();
    cout << Padding(P)<<endl;

    while (true) {
        // 获取当前时间点
        auto currentTime = chrono::steady_clock::now();

        // 计算距离上一次输出的时间间隔
        auto elapsedTime = chrono::duration_cast<chrono::milliseconds>(currentTime - lastOutputTime);

        // 如果时间间隔超过 T 秒，则输出 "Hello, world" 并更新 lastOutputTime
        if (elapsedTime.count() >= Tc * 1000) {
            P = GenerateDynamicPassword(user_name);
            lastOutputTime = currentTime;
            cout << Padding(P) << endl;
        }

        // 休眠一段时间，避免 CPU 占用过高
       //this_thread::sleep_for(chrono::milliseconds(100));
    }
}