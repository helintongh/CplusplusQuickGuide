/*** 
 * @Author: helintongh
 * @Date: 2020-08-25 21:12:11
 * @LastEditTime: 2020-08-25 22:03:54
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/运算符重载/有迭代器的vector.cpp
 */

#include <iostream>

using namespace std;
/*
类模板 => 实现一个C++ STL里面的一个顺序容器 vector 向量容器
SeqStack
Queue
容器:
空间配置器allocator

template<class _Ty,
	class _Alloc = allocator<_Ty>>
	class vector

容器的空间配置器allocator 做四件事情 内存开辟/内存释放   对象构造/对象析构
*/
// 定义容器的空间配置器，和C++标准库的allocator实现一样
template<typename T>
struct Allocator
{
	T* allocate(size_t size) // 负责内存开辟
	{
		return (T*)malloc(sizeof(T) * size);
	}
	void deallocate(void *p) // 负责内存释放
	{
		free(p);
	}
	void construct(T *p, const T &val) // 负责对象构造
	{
		new (p) T(val); // 定位new,在指定的内存上构造一个值为val的对象
	}
	void destroy(T *p) // 负责对象析构
	{
		p->~T(); // ~T()代表了T类型的析构函数
	}
};

/*
容器底层内存开辟，内存释放，对象构造和析构，都通过allocator空间配置器来实现
*/
template<typename T, typename Alloc = Allocator<T>>
class vector
{
public:
	/*
	vector(int size = 10, const Alloc &alloc = Allocator<T>())
		:_allocator(alloc)
	{
		// 实现代码块省略
		// 上面的实现可以让用户自己传一个allocator
	}
	*/
	vector(int size = 10)
	{
		// 需要把内存开辟和对象构造分开处理
		//_first = new T[size];
		_first = _allocator.allocate(size); // 只开辟空间
		_last = _first;
		_end = _first + size;
	}
	~vector()
	{
		// 析构容器有效的元素，然后释放_first指针指向的堆内存
		// delete[]_first;
		for (T *p = _first; p != _last; ++p)
		{
			_allocator.destroy(p); // 把_first指针指向的数组的有效元素进行析构操作
		}
		_allocator.deallocate(_first); // 释放堆上的数组内存
		_first = _last = _end = nullptr;
	}
	vector(const vector<T> &rhs) // 拷贝构造函数
	{
		int size = rhs._end - rhs._first;
		//_first = new T[size];
		_first = _allocator.allocate(size);
		int len = rhs._last - rhs._first;
		for (int i = 0; i < len; ++i)
		{
			//_first[i] = rhs._first[i];
			_allocator.construct(_first+i, rhs._first[i]); // 已有的内存上构造对象
		}
		_last = _first + len;
		_end = _first + size;
	}
	vector<T>& operator=(const vector<T> &rhs) // 赋值构造函数
	{
		if (this == &rhs) // 排除自赋值
			return *this;

		//delete[]_first;
		for (T *p = _first; p != _last; ++p)
		{
			_allocator.destroy(p); // 把_first指针指向的数组的有效元素进行析构操作
		}
		_allocator.deallocate(_first);

		int size = rhs._end - rhs._first;
		//_first = new T[size];
		_first = _allocator.allocate(size);
		int len = rhs._last - rhs._first;
		for (int i = 0; i < len; ++i)
		{
			//_first[i] = rhs._first[i];
			_allocator.construct(_first + i, rhs._first[i]);
		}
		_last = _first + len; // 最后一个元素的后继
		_end = _first + size; // 数组最后一个位置的后继
		return *this;
	}
	void push_back(const T &val) // 向容器末尾添加元素
	{
		if (full())
			expand();
		//*_last++ = val;   _last指针指向的内存构造一个值为val的对象
		_allocator.construct(_last, val); // 在_last位置构造值为val的对象
		_last++;
	}
	void pop_back() // 从容器末尾删除元素
	{
		if (empty())
			return;
		//--_last; // 不仅要把_last指针--，还需要析构删除的元素
		--_last;
		_allocator.destroy(_last); // _last位置的对象析构
	}
	T back()const // 返回容器末尾的元素的值
	{
		return *(_last - 1);
	}
	bool full()const { return _last == _end; } // 判断是否满
	bool empty()const { return _first == _last; } // 判断是否空
	int size()const { return _last - _first; } // 得到元素的大小
private:
	T *_first; // 指向数组起始的位置
	T *_last;  // 指向数组中有效元素的后继位置
	T *_end;   // 指向数组空间的后继位置
	Alloc _allocator; // 定义容器的空间配置器对象

	void expand() // 容器的二倍扩容
	{
		int size = _end - _first;
		//T *ptmp = new T[2 * size];
		T *ptmp = _allocator.allocate(2*size);
		for (int i = 0; i < size; ++i)
		{
			//ptmp[i] = _first[i];
			_allocator.construct(ptmp+i, _first[i]);
		}
		//delete[]_first;
		for (T *p = _first; p != _last; ++p)
		{
			_allocator.destroy(p);
		}
		_allocator.deallocate(_first);
		_first = ptmp;
		_last = _first + size;
		_end = _first + 2 * size;
	}
};

// 定义一个Test类
class Test
{
public:
	Test() { cout << "Test()" << endl; }
	~Test() { cout << "~Test()" << endl; }
	Test(const Test&) { cout << "Test(const Test&)" << endl; }
};
int main()
{
    
}