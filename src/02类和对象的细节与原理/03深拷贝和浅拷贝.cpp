#include <iostream>
using namespace std;

/*
this指针 =》 类-》很多对象  共享一套成员方法
成员方法，方法的参数都会添加一个this指针

构造函数：
	定义对象时，自动调用的；可以重载的；构造完成，对象产生了
析构函数：
	不带参数，不能重载，只有一个析构函数；析构完成，对象就不存在了

.data  上的对象 (程序启动时构造,程序结束时析构)
heap new delete
stack (进入函数时构造,出函数时析构)

对象的浅拷贝和深拷贝
*/

class SeqStack
{
public:
	// 构造函数 
	SeqStack(int size = 10)
	{
		cout << this << " SeqStack()" << endl;
		_pstack = new int[size];
		_top = -1;
		_size = size;
	}
	// 自定义拷贝构造函数 <= 对象的浅拷贝现在有问题了
	SeqStack(const SeqStack &src)
	{
		cout << "SeqStack(const SeqStack &src)" << endl;
		_pstack = new int[src._size];
		for (int i = 0; i <= src._top; ++i)
		{
			_pstack[i] = src._pstack[i];
		}
		_top = src._top;
		_size = src._size;
	}
	// 析构函数
	~SeqStack() 
	{
		cout << this << " ~SeqStack()" << endl;
		delete[]_pstack;
		_pstack = nullptr;
	}
	// 赋值重载函数 s2 = s1;
	void operator=(const SeqStack &src)
	{
		cout << "operator=" << endl;
		// 防止自赋值
		if (this == &src)
			return;

		// 需要先释放当前对象占用的外部资源
		delete[]_pstack;
        // 重新开辟引用的外部资源的空间
		_pstack = new int[src._size];
		for (int i = 0; i <= src._top; ++i)
		{
			_pstack[i] = src._pstack[i];
		}
		_top = src._top;
		_size = src._size;
	}
	void push(int val)
	{
		if (full())
			resize();
		_pstack[++_top] = val;
	}
	void pop()
	{
		if (empty())
			return;
		--_top;
	}
	int top()
	{
		return _pstack[_top];
	}
	bool empty() { return _top == -1; }
	bool full() { return _top == _size - 1; }
private:
	int *_pstack; // 动态开辟数组，存储顺序栈的元素
	int _top; // 指向栈顶元素的位置
	int _size; // 数组扩容的总大小

	void resize()
	{
		int *ptmp = new int[_size * 2];
		for (int i = 0; i < _size; ++i)
		{
			ptmp[i] = _pstack[i];
		} // memcpy(ptmp, _pstack, sizeof(int)*_size); realloc
		delete[]_pstack;
		_pstack = ptmp;
		_size *= 2;
	}
};
int main()
{
	SeqStack s; // 没有提供任何构造函数的时候，会为你生成默认构造和默认析构，是空函数
	SeqStack s1(10);
    /*
        调用拷贝构造函数,默认拷贝构造函数->做直接内存数据拷贝
        s2 操作是浅拷贝,s1和s2都指向同一内存,
        s2先调析构函数->s1调用析构时delete的是野指针
        再类里面自定义拷贝构造函数后,不会出现该问题(进行深拷贝)
    */
	SeqStack s2 = s1; // #1  调用拷贝构造函数,默认拷贝构造函数->做直接内存数据拷贝
	//SeqStack s3(s1); // #2 s3和s2是一模一样的

    // s2 = s1会出错,又是浅拷贝,还把s2指向的资源丢了,需要自定义赋值函数。重载=号
	// s2.operator=(s1) 
	// void operator=(const SeqStack &src)
	s2 = s1; // 默认的赋值函数 => 做直接的内存拷贝 。
    // s1 = s1; // 完全没必要的操作

	return 0;
}