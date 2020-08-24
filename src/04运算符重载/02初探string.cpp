/*** 
 * @Author: helintongh
 * @Date: 2020-08-23 16:03:58
 * @LastEditTime: 2020-08-23 20:26:02
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/运算符重载/初探string.cpp
 */
// C语言是操作char *或者说char [],操作字符串不方便首先大小固定而且字符串连接比较大小需要相应函数。
// char arr[]="jkhsdkf"; 
// C++中string类型就相对简单

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main()
{
    string str1;
    string str2 = "aaa"; // string(const char*)
    string str3 = "bbb"; // 
    string str4 = str2 + str3;
    string str5 = str2 + "ccc";
    string str6 = "ddd" + str2; //说明提供了全局的+重载函数

    cout << "str6:" << str6 << endl; // 重载了<<和>>运算符
    // bool operator>(const String &str)
    if(str5 > str6)
    {
        cout << str5 << " > " << str6 << endl;
    }
    else
    {
        cout << str5 << " < " << str6 << endl;
    }

    int len = str6.length(); //实现了获取字符串长度的成员函数
    for(int i = 0; i < len; ++i)
    {
        cout << str6[i] << " "; // 重载了[]下标运算符
    }
    cout << endl;

    // string -> char*
    char buf[1024] = {0};
    strcpy(buf, str6.c_str()); // string对象拷贝到c的字符串里
    cout << "buf:" << buf << endl;

    return 0;
}