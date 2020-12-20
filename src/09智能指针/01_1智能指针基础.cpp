/*
智能指针:
不带引用计数的智能指针:auto_ptr,scoped_ptr,unique_ptr
带引用计数的智能指针shared_ptr,weak_ptr
智能指针的交叉引用(循环引用)问题
多线程访问共享对象问题
自定义删除器

娱乐任务:自己实现一个智能指针
*/

#include <iostream>

int main()
{
	int *p = new int(10);
	*p = 30;

	delete p;

	return 0;
}