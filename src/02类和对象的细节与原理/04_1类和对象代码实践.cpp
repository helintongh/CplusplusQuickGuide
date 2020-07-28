#include <iostream>
#include <cstring>
using namespace std;

/*
浅拷贝解决方法：自定义拷贝构造函数和赋值重载函数
自定义一个:String类型
后面会实现一个循环队列 Queue
*/
class String
{
public:
	String(const char *str = nullptr) // 普通构造函数
	{
		if (str != nullptr)
		{
			m_data = new char[strlen(str) + 1]; // 先开内存
			strcpy(this->m_data, str); // 再赋值
		}
		else // 处理指针为nullptr的情况
		{
			m_data = new char[1]; // new char; 也要给它开辟一个空间大小
			*m_data = '\0'; // 0
		}
	}
	String(const String &other)  // 拷贝构造函数
	{
		m_data = new char[strlen(other.m_data) + 1];
		strcpy(m_data, other.m_data);
	}
	~String(void)  // 析构函数
	{
		delete[]m_data;
		m_data = nullptr;
	}
	// String& 是为了支持连续的operator=赋值操作 str1 = str2 =str3;
	String& operator=(const String &other) // 赋值重载函数
	{
		if (this == &other)
		{
			return *this;  // str1
		}

		delete[]m_data;

		m_data = new char[strlen(other.m_data) + 1];
		strcpy(m_data, other.m_data);
		return *this; // str1
	}
private:
	char *m_data; // 用于保存字符串
};

int main()
{
	// 调用带const char*参数的构造函数
	String str1;
	String str2("hello");
	String str3 = "world";

	// 调用拷贝构造函数
	String str4 = str3;
	String str5(str3);

	// 调用赋值重载函数
	/*
	str1 = str2
	str1.operator=(str2) => str1
	str3 = str1
	*/
	str3 = str1 = str2;

	return 0;
}