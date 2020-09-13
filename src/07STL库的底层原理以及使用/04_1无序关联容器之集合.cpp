/*** 
 * @Author: helintongh
 * @Date: 2020-09-13 15:09:27
 * @LastEditTime: 2020-09-13 15:21:37
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/STL库/无序关联容器之集合.cpp
 */
#include <iostream>

// 使用无序关联容器包含的头文件
#include <unordered_set> // unordered_set unordered_multiset
#include <unordered_map> // unordered_map unordered_multimap

// 使用有序关联容器包含的头文件  红黑树
#include <set> // set multiset
#include <map> // map multimap
using namespace std;
/*
无序关联容器 => 链式哈希表  增删查O(1) 
set:集合 key   map:映射表 [key,value]
unordered_set 单重集合(单重指不允许key重复)
unordered_multiset 多重集合
unordered_map 单重映射表
unordered_multimap 多重映射表

有序关联容器 => 红黑树 增删查O(log2n) 2是底数(树的层数，树的高度) =>负载均衡的一致性hash算法(既需要增删查又需要顺序)
set
multiset
map
multimap
*/

/*
关联容器：
1.各个容器底层的数据结构 O(1)  O(log2n)
2.常用增删查方法
增加：insert(val)
遍历：iterator自己搜索， 调用find成员方法
删除：erase(key)  erase(it)
*/
int main()
{
    unordered_set<int> set1; // 不会存储key值重复的元素
	for (int i = 0; i < 50; ++i)
	{
		set1.insert(rand()%20+1); // vector/deque/list  insert(it, val) => 关联容器插入操作不一样,不指定位置
	}

	cout << set1.size() << endl;    // 返回元素个数
	cout << set1.count(15) << endl; // 返回值为15的个数

	auto it1 = set1.begin(); // 迭代器遍历
	for (; it1 != set1.end(); ++it1)
	{
		cout << *it1 << " ";
	}
	cout << endl;

	set1.erase(20); // 按key值删除元素

	for (it1 = set1.begin(); it1 != set1.end(); )
	{
		if (*it1 == 30)
		{
			it1 = set1.erase(it1); // 调用erase，如果it1不更新it1迭代器就失效了
		}
		else
		{
			++it1;
		}
	}
	
	it1 = set1.find(20);	// 查找值为20的元素
	if (it1 != set1.end())
	{
		set1.erase(it1);
	}

	for (int v : set1)	// for_each进行输出
	{
		cout << v << " ";
	}
	cout << endl;
}