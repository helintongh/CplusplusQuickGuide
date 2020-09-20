/*** 
 * @Author: helintongh
 * @Date: 2020-09-20 17:36:43
 * @LastEditTime: 2020-09-20 17:38:38
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/STL库/函数对象使用场景2.cpp
 */
#include <iostream>
#include <queue>
#include <vector>
#include <set>
using namespace std;

int main()
{
	set<int, greater<int>> set1; // 修改set的排序方式(红黑树的排序方式)
	for (int i = 0; i < 10; ++i)
	{
		set1.insert(rand() % 100);
	}

	for (int v : set1)
	{
		cout << v << " ";
	}
	cout << endl;

	return 0;
}