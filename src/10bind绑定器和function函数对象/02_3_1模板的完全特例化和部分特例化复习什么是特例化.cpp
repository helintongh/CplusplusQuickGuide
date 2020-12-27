#include <iostream>
#include <typeinfo>
using namespace std;
/*
模板的完全特例化和非完全（部分）特例化
模板的实参推演 => 基本概念很简单
*/
template<typename T>
bool compare(T a, T b)
{
	cout << "template compare" << endl;
	return a > b; // 如果是这个模板那么compare("aaa", "bbb")是比较字符串地址不符合=>需要特例化一个模板函数
}
// 完全特例化的compare模板函数
template<>
bool compare<const char*>(const char*a, const char*b)
{
	cout << "compare<const char*>" << endl;
	return strcmp(a, b) > 0;
}

int main()
{
	compare(10, 20); // 
	compare("aaa", "bbb"); // T const char*
	return 0;
}