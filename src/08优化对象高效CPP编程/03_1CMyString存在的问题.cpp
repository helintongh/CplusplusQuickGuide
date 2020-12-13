#include <iostream>
//#include <vector>
using namespace std;
/*
	普通的左值拷贝构造函数存在一个问题:
	如果我想写一个函数:
	CMyString GetString(CMyString &str)
	{
		const char* pstr = str.c_str();
		CMyString tmpStr(pstr);
		return tmpStr;
	}
	int main()
	{
		CMyString str1("aaaaaaaaaaaaaaaaaaaa");
		CMyString str2;
		str2 = GetString(str1);
		cout << str2.c_str() << endl;

		return 0;
	}
	main函数打印如下:
	CMyString(const char*)
	CMyString(const char*)
	CMyString(const char*)
	CMyString(const CMyString&) => tmpStr拷贝构造main函数栈帧上的临时对象
	~CMyString
	operator=(const CMyString&) => main函数栈帧上的临时对象给t2赋值
	~CMyString
	aaaaaaaaaaaaaaaaaaaa
	~CMyString
	~CMyString

	注意:CMyString(const CMyString&)这两个打印
		说明GetString函数会开辟临时空间用来存储CMyString的指针变量mptr,调用了拷贝,构造,赋值等函数将临时变量传递给了main函数后再销毁再把临时指针置为空。
		那为什么不直接把开辟的临时指针控制权交给main函数呢？
*/
class CMyString
{
public:
	CMyString(const char *str = nullptr)
	{
		cout << "CMyString(const char*)" << endl;
		if (str != nullptr)
		{
			mptr = new char[strlen(str) + 1];
			strcpy(mptr, str);
		}
		else
		{
			mptr = new char[1];
			*mptr = '\0';
		}
	}
	~CMyString()
	{
		cout << "~CMyString" << endl;
		delete[]mptr;
		mptr = nullptr;
	}
	// 带左值引用参数的拷贝构造
	CMyString(const CMyString &str)
	{
		cout << "CMyString(const CMyString&)" << endl;
		mptr = new char[strlen(str.mptr) + 1];
		strcpy(mptr, str.mptr); 
		/*
		能否?
		mptr = str.mptr;
		str.mptr = nullptr;
		*/
	}
	// 带左值引用参数的赋值重载函数
	CMyString& operator=(const CMyString &str)
	{
		cout << "operator=(const CMyString&)" << endl;
		if (this == &str)
			return *this;

		delete[]mptr;

		mptr = new char[strlen(str.mptr) + 1];
		strcpy(mptr, str.mptr);
		return *this;
	}
	const char* c_str()const { return mptr; }
private:
	char *mptr;
};

CMyString GetString(CMyString &str)
{
	const char* pstr = str.c_str();
	CMyString tmpStr(pstr);
	return tmpStr;
}
int main()
{
	CMyString str1("aaaaaaaaaaaaaaaaaaaa");
	CMyString str2;
	str2 = GetString(str1);
	cout << str2.c_str() << endl;

	return 0;
}