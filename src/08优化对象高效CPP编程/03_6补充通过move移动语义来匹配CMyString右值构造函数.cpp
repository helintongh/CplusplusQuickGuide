#include <iostream>
#include <vector>
using namespace std;
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
	}
	// 带右值引用参数的拷贝构造
	CMyString(CMyString &&str)
	{
		cout << "CMyString(CMyString&&)" << endl;
		mptr = str.mptr;
		str.mptr = nullptr;
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
	// 带右值引用参数的赋值重载函数
	CMyString& operator=(CMyString &&str) // 临时对象
	{
		cout << "operator=(CMyString&&)" << endl;
		if (this == &str)
			return *this;

		delete[]mptr;

		mptr = str.mptr;
		str.mptr = nullptr;
		return *this;
	}
	const char* c_str()const { return mptr; }
private:
	char *mptr;
};

vector<CMyString> GetVector()
{
	CMyString str1 = "aaa", str2 = "bbb", str3 = "ccc";
	cout << "------------------------" << endl;

	vector<CMyString> vec;
	vec.reserve(10);
	vec.push_back(std::move(str1));
	vec.push_back(std::move(str2));
	vec.push_back(std::move(str3));

	return vec; // 匹配的是容器的右值引用参数的拷贝构造
}
int main()
{
	vector<CMyString> vec;
	
	vec = GetVector(); // 匹配的是容器的右值引用参数的赋值函数

	return 0;
}