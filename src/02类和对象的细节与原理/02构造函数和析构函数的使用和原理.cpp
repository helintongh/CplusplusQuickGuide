#include <iostream>
using namespace std;

/*
OOP实现一个顺序栈 

构造函数和析构函数
函数的名字和类名一样
没有返回值
*/
class SeqStack
{
public:
	// 构造函数 SeqStack s1;  SeqStack s2(20);
	SeqStack(int size = 10) // 是可以带参数的，因此可以提供多个构造函数，叫做构造函数的重载
	{
		cout << this << " SeqStack()" << endl; // this这里指向对象的内存
		_pstack = new int[size];
		_top = -1;
		_size = size;
	}
	// 析构函数
	~SeqStack() // 是不带参数的，所有析构函数只能有一个
	{
		cout << this << " ~SeqStack()" << endl; // this这里指向地址
		delete []_pstack;
		_pstack = nullptr;
	}
	void push(int val) // 入栈
	{
		if (full()) // 栈满扩容
			resize();
		_pstack[++_top] = val; 
	}
	void pop() // 出栈
	{
		if (empty())
			return;
		--_top;
	}
	int top()
	{
		return _pstack[_top];
	}
	bool empty() { return _top == -1; } // 判断是否为空
	bool full() { return _top == _size - 1; } // 判断是否为满
private:
	int *_pstack; // 动态开辟数组，存储顺序栈的元素
	int _top; // 指向栈顶元素的位置
	int _size; // 数组扩容的总大小

	void resize() // 私有方法,只给public方法调用的
	{
		int *ptmp = new int[_size * 2]; // 扩容两倍
		for (int i = 0; i < _size; ++i)
		{
			ptmp[i] = _pstack[i]; // 原来内存的数据拷贝到新的里
		}
        // 为什么不用以下的函数? 下面涉及的是内存拷贝,在对象里不适合。(深拷贝浅拷贝中的问题) 
        // memcpy(ptmp, _pstack, sizeof(int)*_size); realloc
		delete[]_pstack; // 释放掉原来的内存
		_pstack = ptmp;
		_size *= 2;
	}
};
SeqStack gs; // 全局变量程序结束时才析构
int main() // 先构造的后析构,后构造的先析构 是栈
{

	//  1.开辟内存  2.调用构造函数 
	SeqStack s;
	//s.init(5);  // 对象成员变量的初始化操作

	for (int i = 0; i < 15; ++i)
	{
		s.push(rand() % 100);
	}

	while (!s.empty())
	{
		cout << s.top() << " ";
		s.pop();
	}

	//s.release(); // 释放对象成员变量占用的外部堆内存（外部资源）

	SeqStack s1(50);

	//s1.~SeqStack(); // 析构函数调用以后，我们说对象不存在了,不建议自己掉
    // 析构以后再调用方法的话,堆内存的非法访问了！！！
	s1.push(30); 

    /*
	.data 
	heap
	stack
	*/
	SeqStack *ps = new SeqStack(60); // malloc内存开辟+SeqStack(60)对象构造
	ps->push(70);
	ps->push(80);
	ps->pop();
	cout << ps->top() << endl;
	// 堆上一定得手动释放
    delete ps; //先调用ps->~SeqStack()+然后free(ps)<-delete做了这两个操作   
    // delete和free的区别


	return 0; // 栈上对象在return处析构,调用析构函数
}