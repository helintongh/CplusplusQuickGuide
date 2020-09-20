/*** 
 * @Author: helintongh
 * @Date: 2020-09-20 16:44:23
 * @LastEditTime: 2020-09-20 17:22:18
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/STL库/函数对象的前身函数指针.cpp
 */

#include <iostream>
using namespace std;
/*
函数对象  =>  C语言里面的函数指针
*/

// 使用C的函数指针解决方案
template<typename T>
inline bool mygreater(T a, T b)
{
	return a > b;
}
template<typename T>
inline bool myless(T a, T b)
{
	return a < b;
}
// compare是C++的库函数模板
template<typename T, typename Compare>
bool compare(T a, T b, Compare comp) // Compare推到出来是一个函数指针类型
{
	// 通过函数指针调用函数，是没有办法内联的(发生在编译阶段)，效率很低，因为有函数调用开销
	return comp(a, b);  // operator()(a, b);
}
int main()
{
	cout << compare(10, 20, mygreater<int>) << endl;
	cout << compare(10, 20, myless<int>) << endl;
	//cout << compare('b', 'y') << endl;

	return 0;
}