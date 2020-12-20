#include <iostream>
#include <memory>
using namespace std;
// 对资源进行引用计数的智能指针
template<typename T>
class RefCnt
{
public:
	RefCnt(T *ptr = nullptr)
		:mptr(ptr)
	{
		if(mptr != nullptr)
			mcount = 1;
	}
	void addRef() { mcount++; } // 增加引用计数
	void delRef() { --mcount; }
private:
	T *mptr;
	int mcount;
};


template<typename T>
class CSmartPtr // 非常简单的智能指针
{
public:
	CSmartPtr(T *ptr = nullptr)
		:mptr(ptr) 
	{
		mpRefCnt = new <T>RefCnt();
	}
	~CSmartPtr() 
	{ 
		if(0 == mpRefCnt->delRef())
		{
			delete mptr; 
			mptr = nullptr;
		}
	}
	T& operator*() { return *mptr; } // 返回引用,要改变mptr的值。重载*运算符
	T* operator->() { return mptr; } // 重载->运算符

	CSmartPtr(const CSmartPtr<T> &src)
		:mptr(src.mptr),mpRefCnt(src.mpRefCnt) // 拷贝资源时,先把指针给我,再把引用计数给我
	{
		if(mptr != nullptr)
			mpRefCnt->addRef(); // 引用计数+1
	}
	CSmartPtr<T>& operator=(const CSmartPtr<T> &src)
	{
		if(this == &src)
			return *this; // 防止自赋值

		if(0 == mpRefCnt->delRef())// 减少一个引用计数并判断
		{
			delete mptr;
		}

		mptr = src.mptr;
		mpRefCnt = src.mpRefCnt;
		mpRefCnt>addRef();
		return *this;
	}
private:
	T *mptr;	// 指向资源的指针
	RefCnt<T> *mpRefCnt; // 指向该资源引用计数对象的指针
};

int main()
{
	/*
	带引用计数的智能指针shared_ptr和weak_ptr
	带引用计数:多个智能指针可以管理同一资源
	带引用计数:给每一个对象资源,匹配一个引用计数
	智能指针 => 引用这个资源的时候 => 引用计数+1
	智能指针 => 不使用该资源的时候 => 引用计数-1 => !=0不析构, ==0资源释放
	*/
	CSmartPtr<int> ptr1(new int);
	CSmartPtr<int> ptr2(ptr1);

	return 0;
}