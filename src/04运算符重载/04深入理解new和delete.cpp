/*** 
 * @Author: helintongh
 * @Date: 2020-08-29 11:21:22
 * @LastEditTime: 2020-08-29 15:56:50
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/运算符重载/深入理解new和delete.cpp
 */
#include <iostream>
using namespace std;
/*
new和delete
1.malloc和new的区别？
a.malloc按字节开辟内存的；new开辟内存时需要指定类型 new int[10]
  所以malloc开辟内存返回的都是void*  operator new -> int*
b.malloc只负责开辟空间，new不仅仅有malloc的功能，可以进行数据的初始化
   new int(20);<-赋初值   new int[20];     new int[20]();<-数组每个元素赋为0  int()
c.malloc开辟内存失败返回nullptr指针；new抛出的是bad_alloc类型的异常

2.free和delete的区别？
delete: 先调用析构函数, 再free
如果delete后面就是普通指针,如下:
delete (int*)p 和 free(p) 没有区别

new -> operator new
delete -> operator delete

new和delete能混用吗？C++为什么区分单个元素和数组的内存分配和释放呢？
new delete
new[] delete[]
对于普通的编译器内置类型 new/delete[]   new[]/delete

自定义的类类型，有析构函数，为了调用正确的析构函数，那么开辟对象数组的时候，
会多开辟4个字节，记录对象的个数
*/

// 如果是对象应该:先调用operator new开辟内存空间、然后调用对象的构造函数（初始化）
void* operator new(size_t size)
{
	void *p = malloc(size);
	if (p == nullptr)
		throw bad_alloc();
	cout << "operator new addr:" << p << endl;
	return p;
}
// delete p;  如果是对象应该:调用p指向对象的析构函数、再调用operator delete释放内存空间
void operator delete(void *ptr)
{
	cout << "operator delete addr:" << ptr << endl;
	free(ptr);
}
// 处理数组的new和delete
void* operator new[](size_t size)
{
	void *p = malloc(size);
	if (p == nullptr)
		throw bad_alloc();
	cout << "operator new[] addr:" << p << endl;
	return p;
}
void operator delete[](void *ptr)
{
	cout << "operator delete[] addr:" << ptr << endl;
	free(ptr);
}
int main()
{
  /*
  通过汇编可以看到,new和delete在汇编指令上表现为:
      call operator new 和 call operator delete
  可以得知new和delete本质上是重载函数的调用
  */
  try
  {
    int *p = new int;
    delete p;

    int *q = new int[10];
    delete []q;
  }
  catch (const bad_alloc &err)
  {
    cerr << err.what() << endl;
  }
  
  return 0;
}