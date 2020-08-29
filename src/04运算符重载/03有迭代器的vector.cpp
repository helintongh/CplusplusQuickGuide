/*** 
 * @Author: helintongh
 * @Date: 2020-08-25 21:12:11
 * @LastEditTime: 2020-08-29 11:00:35
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/运算符重载/有迭代器的vector.cpp
 */

#include <iostream>

using namespace std;


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
		new (p) T(val); // 定位new
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
	vector(int size = 10)
	{
		// 需要把内存开辟和对象构造分开处理
		//_first = new T[size];
		_first = _allocator.allocate(size);
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
	vector(const vector<T> &rhs)
	{
		int size = rhs._end - rhs._first;
		//_first = new T[size];
		_first = _allocator.allocate(size);
		int len = rhs._last - rhs._first;
		for (int i = 0; i < len; ++i)
		{
			//_first[i] = rhs._first[i];
			_allocator.construct(_first + i, rhs._first[i]);
		}
		_last = _first + len;
		_end = _first + size;
	}
	vector<T>& operator=(const vector<T> &rhs)
	{
		if (this == &rhs)
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
		_last = _first + len;
		_end = _first + size;
		return *this;
	}
	void push_back(const T &val) // 向容器末尾添加元素
	{
		if (full())
			expand();
		//*_last++ = val;   _last指针指向的内存构造一个值为val的对象
		_allocator.construct(_last, val);
		_last++;
	}
	void pop_back() // 从容器末尾删除元素
	{
		if (empty())
			return;
		// erase(it);  verify(it._ptr, _last); // 检查当前到末尾
		// insert(it, val); verify(it._ptr, _last); 
		verify(_last - 1, _last);
		//--_last; // 不仅要把_last指针--，还需要析构删除的元素
		--_last;
		_allocator.destroy(_last);
	}
	T back()const // 返回容器末尾的元素的值
	{
		return *(_last - 1);
	}
	bool full()const { return _last == _end; }
	bool empty()const { return _first == _last; }
	int size()const { return _last - _first; }
	T& operator[](int index) // 重载[]给vector新增下标运算符vec[2]
	{ 
		if (index < 0 || index >= size())
		{
			throw "OutOfRangeException"; // 下标非法,抛出异常
		}
		return _first[index]; 
	}

	// insert erase

	// #1迭代器一般实现成容器的嵌套类型,因为不同容器操作不同
	class iterator
	{
	public:
		friend class vector<T, Alloc>;
		iterator(vector<T, Alloc> *pvec=nullptr
			, T *ptr = nullptr) // 迭代器构造函数
			:_ptr(ptr), _pVec(pvec)
		{
			Iterator_Base *itb = 
				new Iterator_Base(this, _pVec->_head._next);
			_pVec->_head._next = itb;
		}
		bool operator!=(const iterator &it)const
		{
			// 检查迭代器的有效性
			if (_pVec == nullptr || _pVec != it._pVec)
			{
				throw "iterator incompatable!";
			}
			return _ptr != it._ptr; // 当前迭代器指针 _p 与 迭代器指针it._p进行比较
		}
		void operator++()
		{
			// 检查迭代器的有效性
			if (_pVec == nullptr)
			{
				throw "iterator invalid!";
			}
			_ptr++; // 指针++即可
		}
		T& operator*() // int data = *it; *it = 20; => 不加const可以修改,迭代器解引用可赋值
		{ 
			// 检查迭代器的有效性
			if (_pVec == nullptr)
			{
				throw "iterator invalid!";
			}
			return *_ptr; 
		} 
		const T& operator*()const 
		{ 
			// 检查迭代器的有效性
			if (_pVec == nullptr)
			{
				throw "iterator invalid!";
			}
			return *_ptr; 
		}
	private:
		T *_ptr; // 容器底层需要什么样的变量来遍历就声明成什么样
		// 当前迭代器迭代器是哪个容器对象
		vector<T, Alloc> *_pVec;
	};
	// 需要给容器提供begin和end方法
	iterator begin() { return iterator(this, _first); }
	iterator end() { return iterator(this, _last); }

	// 检查迭代器失效(遍历链表)
	void verify(T *first, T *last)
	{
		Iterator_Base *pre = &this->_head; // 头节点
		Iterator_Base *it = this->_head._next;
		while (it != nullptr)
		{
			if (it->_cur->_ptr > first && it->_cur->_ptr <= last) // 判断是否在检查范围类
			{
				// 迭代器失效，把iterator持有的容器指针置nullptr
				it->_cur->_pVec = nullptr;
				// 删除当前迭代器节点，继续判断后面的迭代器节点是否失效
				pre->_next = it->_next;
				delete it;
				it = pre->_next;
			}
			else
			{
				pre = it;
				it = it->_next;
			}
		}
	}

	// 自定义vector容器insert方法的实现
	iterator insert(iterator it, const T &val)
	{
		/* 
		1.不考虑扩容 verify(_first - 1, _last);
		2.不考虑it._ptr的指针合法性
		*/
		/*
		指定位置插入,1.存在的元素往后移一位 2.依次析构 3. 在当前位置插入
		*/
		verify(it._ptr - 1, _last);
		T *p = _last;
		while (p > it._ptr)
		{
			_allocator.construct(p, *(p-1)); // 当前位置构造一个值为*(p-1)的新对象
			_allocator.destroy(p - 1); // 析构p-1位置对象
			p--;
		}
		// 循环结束后p指向要插入的位置
		_allocator.construct(p, val);
		_last++;
		return iterator(this, p);
	}

	// 自定义vector容器erase方法的实现
	// 1. 析构掉当前元素 2. 当前位置构造一个与后边值相同的元素
	iterator erase(iterator it)
	{
		verify(it._ptr - 1, _last);
		T *p = it._ptr;
		while (p < _last-1) // p!=_last 会越界,析构掉了最后一个元素
		{
			_allocator.destroy(p); // 析构当前元素
			_allocator.construct(p, *(p + 1));
			p++;
		}
		_allocator.destroy(p);
		_last--;
		return iterator(this, it._ptr);
	}

private:
	T *_first; // 指向数组起始的位置
	T *_last;  // 指向数组中有效元素的后继位置
	T *_end;   // 指向数组空间的后继位置
	Alloc _allocator; // 定义容器的空间配置器对象

	// 容器迭代器失效增加代码
	struct Iterator_Base
	{
		Iterator_Base(iterator *c=nullptr, Iterator_Base *n=nullptr)
			:_cur(c), _next(n) {}
		iterator *_cur; // 指向某个迭代器位置的指针
		Iterator_Base *_next; // 指向下一个迭代器Iterator_Base的地址
	};
	Iterator_Base _head; // 定义一个头节点

	void expand() // 容器的二倍扩容
	{
		int size = _end - _first;
		//T *ptmp = new T[2 * size];
		T *ptmp = _allocator.allocate(2 * size);
		for (int i = 0; i < size; ++i)
		{
			//ptmp[i] = _first[i];
			_allocator.construct(ptmp + i, _first[i]);
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

int main()
{
	//测试vector基本功能的代码
#if 0
    vector<int> vec;
    for(int i = 0; i < 20; ++i)
    {
        vec.push_back(rand() % 100 + 1);
    }

    int size = vec.size();
    for(int i = 0; i < size; ++i)
    {
        cout << vec[i] << " "; // 不是每个容器都重载了下标运算符,有的容器是非线行的
    }
    cout << endl;

    vector<int>::iterator it = vec.begin(); // 可以用 auto it = vec.begin();替换左边语句
    for(; it != vec.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    // foreach
	for (int val : vec) // 其底层原理，就是通过容器的迭代器来实现容器遍历的
	{
		cout << val << " ";
	}
	cout << endl;
#endif
	// 测试 insert和erase的代码
	vector<int> vec1(200);
    for(int i = 0; i < 20; ++i)
    {
        vec1.push_back(rand() % 100 + 1);
    }
    // 给vec容器中所有的偶数前面添加一个小于偶数值1的数字
	auto it1 = vec1.begin();
	for (; it1 != vec1.end(); ++it1)
	{
		if (*it1 % 2 == 0)
		{
			it1 = vec1.insert(it1, *it1-1); // 改为vec1.insert(it1, *it1-1)就会迭代器失效
			++it1; 
		}
	}

	for(int v : vec1)
	{
		cout << v << " ";
	}
	cout << endl;

    return 0;
}
