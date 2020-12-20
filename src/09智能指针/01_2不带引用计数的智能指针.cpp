#include <iostream>
#include <memory>
using namespace std;
template<typename T>
class CSmartPtr // 非常简单的智能指针
{
public:
	CSmartPtr(T *ptr = nullptr)
		:mptr(ptr) {}
	CSmartPtr(const CSmartPtr<T> &src) // 防止浅拷贝,拷贝构造函数,但是这样p1和p2其实就指向了不一样的空间了
	{
		mptr = new T(*src.mptr);
	}
	~CSmartPtr() 
	{ 
		delete mptr; 
		mptr = nullptr;
	}
	T& operator*() { return *mptr; } // 返回引用,要改变mptr的值。重载*运算符
	T* operator->() { return mptr; } // 重载->运算符
private:
	T *mptr;
};

int main()
{
	/*
		不带引用计数的智能指针
		C++03:	
			auto_ptr--已废弃
		C++11:
			scoped_ptr--针对auto_ptr做的改进
				scoped_ptr(const scoped_ptr<T>&) = delete;
				scoped_ptr<T>& operator=(const scoped_ptr<T>&) = delete;
				scoped_ptr的拷贝构造和赋值构造函数直接被删除了
		
			unique_ptr
				unique_ptr(const unique_ptr<T>&) = delete;
				unique_ptr<T>& operator=(const unique_ptr<T>&) = delete;
				
				unique_ptr也删除了拷贝构造和赋值构造函数,但是提供了右值版本的拷贝构造和赋值构造函数

				unique_ptr<unique_ptr<T> &&src)
				unique_ptr<T>& operator=(unique_ptr<T>&& src)
				// 下面的代码可运行,因为提供了右值引用参数的拷贝构造和赋值构造函数
				template<typename T>
				unique_ptr<T> getSmartPtr()
				{
					unique_ptr<T> ptr(new T());
					return ptr;
				}

				unique_ptr<int> ptr1 = getSmartPtr<int>();
				ptr1 = getSmartPtr<int>();


		怎么解决浅拷贝问题?同时两个指针指向同一块地址

	*/
	// std::move => c++11 右值引用 std::move得到当前遍历的右值类型
	unique_ptr<int> p1(new int);
	unique_ptr<int> p2(std::move(p1));

	// *p1一定会失败,因为p1的资源已经移动给p2。是显示的资源转移

	/*
	1. 之前的CSmartPtr存在的问题

	CSmartPtr<int> p1(new int);
	CSmartPtr<int> p2(p1); 
	// p1 p2 => new int => 用户认为操作的始终是同一块资源
	*p1 = 20;
	*p2 = 30;
	*/
	auto_ptr<int> ptr1(new int); // 永远让最后一个智能指针掌握资源,之前的置为nullptr。会转移资源所有权到最新的指针,之前的置为空
	auto_ptr<int> ptr2(ptr1);

	*ptr2 = 20;
	//cout << *ptr1 << endl; // 程序崩溃
	// 所以被废弃且不推荐使用auto_ptr， vector<auto_ptr<int>> vec1; vec2(vec1); -> 不要在容器中使用auto_ptr



	return 0;
}