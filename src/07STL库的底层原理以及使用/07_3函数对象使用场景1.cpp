/*** 
 * @Author: helintongh
 * @Date: 2020-09-20 17:27:56
 * @LastEditTime: 2020-09-20 17:40:27
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/STL库/函数对象使用场景1.cpp
 */
#include <iostream>
#include <queue>
#include <vector>
#include <set>
using namespace std;

int main()
{
	priority_queue<int> que1; // vector,使用大根堆从大到小出队
	for (int i = 0; i < 10; ++i)
	{
		que1.push(rand() % 100);
	}

	while (!que1.empty())
	{
		cout << que1.top() << " ";
		que1.pop();
	}
	cout << endl;
	/*
		priority_queue<int, vector<int>, greater<int>> que2;
	*/
	using MinHeap = priority_queue<int, vector<int>, greater<int>>; // using定义新类型,小根堆
	MinHeap que2; // vector
	for (int i = 0; i < 10; ++i)
	{
		que2.push(rand() % 100);
	}

	while (!que2.empty())
	{
		cout << que2.top() << " ";
		que2.pop();
	}
	cout << endl;

	return 0;
}