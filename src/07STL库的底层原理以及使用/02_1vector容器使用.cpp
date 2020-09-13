/*** 
 * @Author: helintongh
 * @Date: 2020-09-12 21:29:02
 * @LastEditTime: 2020-09-13 10:10:42
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/STL库/vector容器使用.cpp
 */
#include <iostream>
#include <vector>
using namespace std;
/*
vector：向量容器 
底层数据结构：动态开辟的数组，每次以原来空间大小的2倍进行扩容的

注:容器扩容=>扩容开辟新空间后,把之前的数据放入新空间然后析构原数据=>通过allocator空间适配器实现=> allocate,deallocate,construct,destroy

vector<int> vec;
增加:
vec.push_back(20); 末尾添加元素 O(1)   导致容器扩容
vec.insert(it, 20); it迭代器指向的位置添加一个元素20  数组的插入 => O(n)   导致容器扩容

删除:
vec.pop_back(); 末尾删除元素 O(1) 
vec.erase(it); 删除it迭代器指向的元素 O(n)

查询:
operator[] 下标的随机访问vec[5]  O(1)
iterator迭代器进行遍历
find，for_each
foreach => 通过iterator来实现的

注意：对容器进行连续插入或者删除操作(insert/erase)，一定要更新迭代器，否则第一次insert或者erase完成，
迭代器就失效了!!!

常用方法介绍:
size()
empty()
reserve(20)：vector预留空间的   只给容器底层开辟指定大小的内存空间，并不会添加新的元素
resize(20)：容器扩容用的  不仅给容器底层开辟指定大小的内存空间，还会添加新的元素
swap ： 两个容器进行元素交换

*/
int main()
{
	vector<int> vec; // vector<string> vec; 声明后空间为0 插入一个此时空间为1 到 2 4 8 16 32 64 ......
	//vec.reserve(20); // 给vector容器预留空间
	vec.resize(20);

	cout << vec.empty() << endl;// 执行reserve的话打印1指vec为空   执行resize打印0指不为空
	cout << vec.size() << endl; // 执行reserve的话打印0            执行resize打印20,添加了20个0值

	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand()%100 + 1);
	}

	cout << vec.empty() << endl;
	cout << vec.size() << endl;



	// vector的operator[]运算符重载函数
	int size = vec.size();
	for (int i = 0; i < size; ++i)
	{
		cout << vec[i] << " ";
	}
	cout << endl;

	// 把vec容器中所有的偶数全部删除
	auto it2 = vec.begin();
	while (it2 != vec.end())
	{
		if (*it2 % 2 == 0)
		{
			it2 = vec.erase(it2); // 不更新it2则迭代器失效
		}
		else
		{
			++it2;
		}
	}

	// 通过迭代器遍历vector容器
	auto it1 = vec.begin();
	for (; it1 != vec.end(); ++it1)
	{
		cout << *it1 << " ";
	}
	cout << endl;

	// 给vector容器中所有的奇数前面都添加一个小于奇数1的偶数   44 45 56 57
	for (it1 = vec.begin(); it1 != vec.end(); ++it1)
	{
		if (*it1 % 2 != 0)
		{
			it1 = vec.insert(it1, *it1-1); // it1是插入位置,*it-1是添加一个小于it位置的奇数1的偶数这一数据
			++it1;  // 找到偶数加两次。如果在47前添加46,然后如果迭代器只进行循环体的++操作,那么迭代器添加完46后指向47位置又再47之前加一个46。
		}
	}

	for (it1 = vec.begin(); it1 != vec.end(); ++it1)
	{
		cout << *it1 << " ";
	}
	cout << endl;


	return 0;
}