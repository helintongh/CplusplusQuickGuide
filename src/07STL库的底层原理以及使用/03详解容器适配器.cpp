/*** 
 * @Author: helintongh
 * @Date: 2020-09-13 14:39:19
 * @LastEditTime: 2020-09-13 14:56:27
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/STL库/详解容器适配器.cpp
 */
#include <cstdlib>
#include <iostream>
#include <stack>    // stack
#include <queue>    // queue和priority_queue
using namespace std;
/*
标准容器 - 容器适配器 => 设计模式，就叫做适配器模式(代理模式)
怎么理解这个适配器？
1.适配器底层没有自己的数据结构，它是另外一个容器的封装，它的方法全部由底层依赖的容器进行实现的
2.没有实现自己的迭代器

// 下面是stack的精简代码,stack不传容器参数那么默认用的deque作为底层
template<typename T, typename Container=deque<T>>
class Stack
{
public:
	void push(const T &val) { con.push_back(val); }
	void pop() { con.pop_back(); }
	T top()const { return con.back(); }
private:
	Container con;
};

stack: push入栈  pop出栈  top查看栈顶元素  empty判断栈空  size返回元素个数 

queue: push入队  pop出队  front查看队头元素 back查看队尾元素  empty判断队空   size返回元素个数
queue => deque  为什么不依赖vector呢？？？
stack => deque  为什么不依赖vector呢？？？
1.vector的初始内存使用效率太低了！没有deque好  queue<int> stack<int>  vector 0-1-2-4-8 deque 4096/sizeof(int) = 1024
2.对于queue来说，需要支持尾部插入，头部删除，O(1)  如果queue依赖vector，其出队效率很低
3.vector需要大片的连续内存，而deque只需要分段的内存，当存储大量数据时，显然deque对于内存的利用率更好一些

priority_queue: push入队  pop出队  top查看队顶元素  empty判断队空  size返回元素个数  默认：大根堆 => 处理top k很好用
priority_queue => vector 为什么依赖vector？？？
底层默认把数据组成一个大根堆结构(树结构) => 在一个内存连续的数组上构建一个大根堆或者小根堆的(下标间的关系判断是否左右孩子节点和根节点)
*/
int main()
{
	priority_queue<int> pque; // 优先级队列不是先进先出,而是优先级越大先出
	for (int i = 0; i < 20; ++i)
	{
		pque.push(rand() % 100 + 1);
	}
	cout << pque.size() << endl;
	while (!pque.empty())
	{
		cout << pque.top() << " "; // 从大到小出队
		pque.pop();
	}


	cout << endl;
	cout << "---------------------------" << endl;

	queue<int> que;
	for (int i = 0; i < 20; ++i)
	{
		que.push(rand() % 100 + 1); // 入队
	}
	cout << que.size() << endl;
	while (!que.empty())
	{
		cout << que.front() << " "; // 队头元素
		que.pop();                  // 出队
	}

	cout << endl;
	cout << "---------------------------" << endl;
	
	stack<int> s1;
	for (int i = 0; i < 20; ++i)
	{
		s1.push(rand() % 100 + 1); // 入栈
	}

	cout << s1.size() << endl; // size返回元素个数

	while (!s1.empty()) // 如果栈不为空
	{
		cout << s1.top() << " "; // 查看栈顶元素
		s1.pop(); // 出栈
	}
	
	return 0;
}
