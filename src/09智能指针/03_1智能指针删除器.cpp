#include <iostream>
#include <memory>
#include <functional>
using namespace std;
/*
智能指针删除器
智能指针:能够保证资源绝对的释放 delete ptr;
*/
// unique_ptr shared_ptr
/*
~unique_ptr() { ...(是一个函数调用); deletor(ptr); } 
template<typename T>
class default_delete
{
public:
	void operator() (T *ptr)
	{
		delete ptr;
	}
}
*/
template<typename T>
class MyDeletor
{
public:
	void operator() (T *ptr) const
	{
		cout << "call MyDeletor operator()!!" << endl;
		delete []ptr;
	}
};
template<typename T>
class MyFileDeletor
{
public:
	void operator() (T *ptr) const
	{
		cout << "call MyFileDeletor operator()!!" << endl;
		fclose(ptr);
	}
};

int main()
{
	// 自定义释放资源的方法
	unique_ptr<int, MyDeletor<int>> ptr1(new int[100]); // delete []ptr;
	unique_ptr<FILE, MyFileDeletor<FILE>> ptr2(fopen("data.txt", "w"));
	/*
		每个释放方式写一个资源释放函数会造成大量代码冗余。
			有没有办法直接写在unique_ptr中,指定释放资源的函数
		lambda表达式 => 函数对象 function
	*/
	// function 指定函数对象返回类型为void,参数为int*
	unique_ptr<int, function<void(int*)>> ptr3 (new int[100],
		[](int *p)->void {
			cout << "call lambda release new int[100]" << endl;
			delete []p;
		}
	);
	unique_ptr<FILE, function<void(FILE*)>>ptr4 (fopen("data.txt","w"),
		[](FILE *p)->void {
			cout << "call lambda release fopen" << endl;
			delete []p;
		}
	);
	
	return 0;
}