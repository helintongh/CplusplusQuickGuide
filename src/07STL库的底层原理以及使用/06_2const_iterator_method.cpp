/*** 
 * @Author: helintongh
 * @Date: 2020-09-20 13:43:36
 * @LastEditTime: 2020-09-20 16:41:03
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/STL库/const_iterator_method.cpp
 */
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

/*
容器的迭代器
const_iterator:常量的正向迭代器  只能读，而不能写了
iterator:普通的正向迭代器 => 打印元素从第一个到最后一个,并且可以修改迭代器所指向的值
reverse_iterator:普通的反向迭代器
const_reverse_iterator:常量的反向迭代器
*/
int main()
{
	vector<int> vec;
	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand() % 100);
	}

	// vector<int>::iterator
	// auto it1 = vec.begin(); 
	// const_iterator   <=   iterator 
    // 左值是const_iterator而其实返回的是iterator类型,这是两个不同的类型 
    // why？const_iterator可以接收iterator <= iterator是由const_iterator派生而来的
	/*
	class const_iterator
	{
	public:
		const T& operator*(){return *_ptr;}
	}
	class iterator : public const_iterator
	{
		T& operator*(){return *_ptr;}
	}
	*/
	// 正向迭代器 
	vector<int>::const_iterator it1 = vec.begin();
	for (; it1 != vec.end(); ++it1)
	{
		cout << *it1 << " ";
	}
	cout << endl;

	// 反向迭代器
	// rbegin()：返回的是最后一个元素的反向迭代器表示
	// rend：返回的是首元素前驱位置的迭代器的表示
	// vector<int>::reverse_iterator
	vector<int>::const_reverse_iterator rit = vec.rbegin();
	for (; rit != vec.rend(); ++rit)
	{
		cout << *rit << " ";
	}
	cout << endl;


	cout << endl;

	return 0;
}