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
    ss >> numStr;  //��res=23 Ӧ��Ϊ000023
    for (int i = 6 - numStr.size(); i < 6; i++) {
        res[i]=numStr[i - (6 - numStr.size())];
    }
    return res;
}

void FlushShowPassword() {
    string user_name;
    cout << "==================MotionPro�ͻ���=====================" << endl;
    cout << "����������û�����";
    cin >> user_name;
    uint32_t P;
    // ��¼��һ�������ʱ���
    P = GenerateDynamicPassword(user_name);
    auto lastOutputTime = chrono::steady_clock::now();
    cout << Padding(P)<<endl;

    while (true) {
        // ��ȡ��ǰʱ���
        auto currentTime = chrono::steady_clock::now();

        // ���������һ�������ʱ����
        auto elapsedTime = chrono::duration_cast<chrono::milliseconds>(currentTime - lastOutputTime);

        // ���ʱ�������� T �룬����� "Hello, world" ������ lastOutputTime
        if (elapsedTime.count() >= Tc * 1000) {
            P = GenerateDynamicPassword(user_name);
            lastOutputTime = currentTime;
            cout << Padding(P) << endl;
        }

        // ����һ��ʱ�䣬���� CPU ռ�ù���
       //this_thread::sleep_for(chrono::milliseconds(100));
    }
}