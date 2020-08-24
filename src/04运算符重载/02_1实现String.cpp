/*** 
 * @Author: helintongh
 * @Date: 2020-08-23 20:19:11
 * @LastEditTime: 2020-08-23 20:57:31
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/运算符重载/实现String.cpp
 */

#include <iostream>
#include <cstring>
//#include <string>
using namespace std;
// 自己实现一个字符串对象
class String
{
public:
	String(const char *p = nullptr)
	{
		if (p != nullptr)
		{
			_pstr = new char[strlen(p) + 1]; // strlen是有效字符的个数
			strcpy(_pstr, p);
		}
		else
		{
			_pstr = new char[1]; // 为空开辟一个空间赋值为'\0'
			*_pstr = '\0';
		}
	}
	~String() 
	{
		delete[]_pstr;
		_pstr = nullptr;
	}
	String(const String &str) // 拷贝构造函数
	{
		_pstr = new char[strlen(str._pstr) + 1];
		strcpy(_pstr, str._pstr);
	}
	String& operator=(const String &str) // 赋值构造函数
	{
		if (this == &str) // 防止自赋值
			return *this;

		delete[]_pstr; // 释放原先的内存

		_pstr = new char[strlen(str._pstr) + 1];
		strcpy(_pstr, str._pstr);
		return *this;
	}
    // < > 和 ==符号的重载
	bool operator>(const String &str)const
	{
		return strcmp(_pstr, str._pstr) > 0;
	}
	bool operator<(const String &str)const
	{
		return strcmp(_pstr, str._pstr) < 0;
	}
	bool operator==(const String &str)const
	{
		return strcmp(_pstr, str._pstr) == 0;
	}

	int length()const { return strlen(_pstr); } // 返回字符串长度
	const char* c_str()const { return _pstr; }  // 转为C语言格式的字符串
	// char ch = str6[6];  str6[6] = '7'
	char& operator[](int index) { return _pstr[index]; } // 重载[]运算符,普通方法可修改
	// char ch = str6[6];  不允许修改！str6[6] = '7'
	const char& operator[](int index)const { return _pstr[index]; } // 常方法不允许修改

private:
	char *_pstr; // String是对char*的封装

	friend String operator+(const String &lhs, const String &rhs); // 拼接字符串
	friend ostream& operator<<(ostream &out, const String &str); // 重载<<，让cout能够输出字符串
};
/*
String operator+(const String &lhs, const String &rhs)
{
    char *ptmp = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];
    strcpy(ptmp, lhs._pstr);
	strcat(ptmp, rhs._pstr); // 直接连接不行,要考虑字符串内存空间
    String tmp(ptmp);
    delete[]ptmp;
    return tmp; // 拷贝了多次,下面的实现更优
}
*/
String operator+(const String &lhs, const String &rhs)
{
	//char *ptmp = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];
	String tmp;
	tmp._pstr = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];
	strcpy(tmp._pstr, lhs._pstr);
	strcat(tmp._pstr, rhs._pstr); // 直接连接不行,要考虑字符串内存空间
	//delete[]ptmp;
	return tmp; // 不用delete是因为放在String对象中,自动析构
}
ostream& operator<<(ostream &out, const String &str)
{
	out << str._pstr;
	return out;
}

int main()
{
	String str1;
	String str2 = "aaa"; // string(const char*)
	String str3 = "bbb";
	String str4 = str2 + str3;
	String str5 = str2 + "ccc";
	String str6 = "ddd" + str2;

	cout << "str6:" << str6 << endl;
	// bool operator>(const String &str)
	if (str5 > str6)
	{
		cout << str5 << " > " << str6 << endl;
	}
	else
	{
		cout << str5 << " < " << str6 << endl;
	}

	int len = str6.length();
	for (int i = 0; i < len; ++i)
	{
		//    char& str6.operator[](i)
		cout << str6[i] << " ";
	}
	cout << endl;

	// string -> char*
	char buf[1024] = { 0 };
	strcpy(buf, str6.c_str());
	cout << "buf:" << buf << endl;


	return 0;
}