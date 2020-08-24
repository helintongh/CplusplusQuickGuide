/*** 
 * @Author: helintongh
 * @Date: 2020-08-23 20:19:11
 * @LastEditTime: 2020-08-24 22:41:37
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

	// 给String字符串类型提供迭代器的实现
	class iterator
	{
	public:
		iterator(char *p = nullptr) :_p(p) {}
		bool operator!=(const iterator &it) // 实现!=的重载
		{
			return _p != it._p; // 当前迭代器指针 _p 与 迭代器指针it._p进行比较
		}
		void operator++() // 实现++的重载
		{
			++_p;
		}
		char& operator*() { return *_p; } // 迭代器解引用
	private:
		char *_p; // 用指针来访问String底层的每一个char型元素
	};
	// begin返回的是容器底层首元素的迭代器的表示
	iterator begin() { return iterator(_pstr); }
	// end返回的是容器末尾元素后继位置的迭代器的表示
	iterator end() { return iterator(_pstr + length()); }
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
	String tmp;	// 直接定义一个String对象
	tmp._pstr = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1]; // 直接对String对象进行内存开辟
	strcpy(tmp._pstr, lhs._pstr);
	strcat(tmp._pstr, rhs._pstr); // 直接连接不行,要考虑字符串内存空间
	//delete[]ptmp;
	return tmp; // 不用delete是因为tmp是String对象,自动析构
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

    // 迭代器的实现的测试代码
    	// 迭代器的功能：提供一种统一的方式，来透明的遍历容器
	String str = "hello world!"; // str叫容器吗？是的.. 底层放了一组char类型的字符
	// 容器的迭代器类型 iterator
	//String::iterator it = str.begin();
	auto it = str.begin();
	for (; it != str.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;

	// c++11 foreach的方式来遍历容器的内部元素的值=>底层，还是通过迭代器进行遍历的
	for(char ch : str) // 依赖于迭代器的begin和end函数,本质上和上面的实现一致
	{
		cout << ch << " ";
	}
	cout << endl;

	return 0;
}