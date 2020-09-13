/*** 
 * @Author: helintongh
 * @Date: 2020-09-13 16:20:38
 * @LastEditTime: 2020-09-13 16:27:58
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/STL库/无序关联容器的使用场景.cpp
 */
#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;
int main()
{
	// 处理海量数据查重复；去重复的时候
	const int ARR_LEN = 100;
	int arr[ARR_LEN] = { 0 };
	for (int i = 0; i < ARR_LEN; ++i)
	{
		arr[i] = rand() % 100 + 1;
	}

    // 1.上面的10万个整数中，统计哪些数字重复了，并且统计数字重复的次数
	unordered_map<int, int> map1;
	for (int k : arr)
	{
		
		auto it = map1.find(k); // 查询k值
		if (it == map1.end())   // 迭代器为end说明数字没有出现过
		{
			map1.insert({k, 1}); // 插入
		}
		else
		{
			it->second++;        // 数字出现过,出现次数++
		}
		
		//map1[k]++; // map1[k]  [k, 1] =>上述代码可简化为左边注释掉的代码
	}

	
	for (const pair<int, int> &p : map1) // &p防止发生拷贝构造,如果pair<int ,int> &p : map1会出错
	{
		if (p.second > 1) // 次数大于1说明有重复的
		{
			cout << "key:" << p.first << " count:" << p.second << endl;
		}
	}
	
    //  迭代器遍历替代for_each也可
	auto it = map1.begin();
	for (; it != map1.end(); ++it)
	{
		if (it->second > 1)
		{
			cout << "key:" << it->first <<
				" count:" << it->second << endl;
		}
	}

	// 2.上面的10万个整数中，把数字进行去重打印  set  map
	unordered_set<int> set;
	for (int v : arr) // O(n)
	{
		set.insert(v); // O(1)
	}

	for (int v : set)
	{
		cout << v << " ";
	}
	cout << endl;



}