/*** 
 * @Author: helintongh
 * @Date: 2020-08-16 21:35:17
 * @LastEditTime: 2020-08-16 21:43:10
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/C++模板/初始vector.cpp
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
/*
类模板 => 实现一个C++ STL里面的一个顺序容器 vector 向量容器
SeqStack
Queue
容器:
*/
/*
容器底层内存开辟，内存释放，对象构造和析构
*/
template<typename T>
class vector
{
public:
	vector(int size = 10)
	{
		// 需要把内存开辟和对象构造分开处理
		_first = new T[size];
		_last = _first;
		_end = _first + size;
	}
	~vector()
	{
		// 析构容器有效的元素，然后释放_first指针指向的堆内存
		delete[]_first;
		_first = _last = _end = nullptr;
	}
	vector(const vector<T> &rhs) // 拷贝构造函数
	{
		int size = rhs._end - rhs._first;
		_first = new T[size];
		int len = rhs._last - rhs._first;
		for (int i = 0; i < len; ++i)
		{
			_first[i] = rhs._first[i];
		}
		_last = _first + len;
		_end = _first + size;
	}
	vector<T>& operator=(const vector<T> &rhs) // 赋值构造函数
	{
		if (this == &rhs) // 排除自赋值
			return *this;

		delete[]_first;

		int size = rhs._end - rhs._first;
		_first = new T[size];
		int len = rhs._last - rhs._first;
		for (int i = 0; i < len; ++i)
		{
			_first[i] = rhs._first[i];
		}
		_last = _first + len; // 最后一个元素的后继
		_end = _first + size; // 数组最后一个位置的后继
		return *this;
	}
	void push_back(const T &val) // 向容器末尾添加元素
	{
		if (full())
			expand();
		*_last++ = val;   //_last指针指向的内存构造一个值为val的对象
	}
	void pop_back() // 从容器末尾删除元素
	{
		if (empty())
			return;
		--_last; // 不仅要把_last指针--，还需要析构删除的元素
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
	void expand() // 容器的二倍扩容
	{
		int size = _end - _first;
		T *ptmp = new T[2 * size];
		for (int i = 0; i < size; ++i)
		{
			ptmp[i] = _first[i];
		}
		delete[]_first;
		_first = ptmp;
		_last = _first + size;
		_end = _first + 2 * size;
	}
};


int main()
{
    vector<int> vec;
    for(int i = 0; i < 20; ++i)
    {
        vec.push_back(rand() % 100);
    }

    vec.pop_back(); //删除末尾

    while(!vec.empty())
    {
        cout << vec.back() << " "; // 返回末尾的值
        vec.pop_back(); 
    }
    cout << endl;

	return 0;
}