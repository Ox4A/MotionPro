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
    ss >> numStr;  //��res=23 Ӧ��Ϊ000023
    for (int i = 6 - numStr.size(); i < 6; i++) {
        res[i]=numStr[i - (6 - numStr.size())];
    }
    return res;
}

void DynamicPasswdVerify() {
    uint32_t P;
    string verify_passwd;
    string standard_passwd;
    cout << "==================MotionPro������=====================" << endl;
    string user_name;
    cout << "����������û�����";
    cin >> user_name;
    P = GenerateDynamicPassword(user_name);
    standard_passwd = Padding(P);
    cout << "��������Ķ�̬���";
    cin >> verify_passwd;
    while (true) {
        if (verify_passwd == standard_passwd) {
            cout << "��֤ͨ������ӭ���뽻��VPN" << endl;
            break;
        }
        else {
            cout << "��֤ʧ�ܣ����������붯̬���";
            cin >> verify_passwd;
            P = GenerateDynamicPassword(user_name);
            standard_passwd = Padding(P);
        }
    }
}