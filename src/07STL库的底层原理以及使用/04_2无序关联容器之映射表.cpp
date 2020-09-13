/*** 
 * @Author: helintongh
 * @Date: 2020-09-13 16:05:29
 * @LastEditTime: 2020-09-13 16:15:21
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/STL库/无序关联容器之映射表.cpp
 */
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;
int main()
{
    /*
	[key, value]
	struct pair
	{
	 first; => key
	 second; => value
	}

	map的operator[]
	1.查询
	2.如果key不存在，它会插入一对数据[key, string()]
	V& operator[](const K &key)
	{
		insert({key, V()});
	}
	*/
    unordered_map<int, string> map1;
	map1.insert(make_pair(1000, "张三"));// make_pair键值对打包成pair对象
	map1.insert({1010, "李四"}); // map表增加元素
	map1.insert({1020, "王五" });
	map1.insert({1030, "王凯" });

    //map1[2000]; // key:2000 value:"" => map1.size()值变为5
    //map1[2000] = "刘硕"; // 相当于map1.insert({2000, "刘硕"});
	//map1[1000] = "张三2"; // 修改操作,此时{1000, "张三"}变为{1000, "张三2"}
	//cout << map1.size() << endl;
    cout << map1.size() << endl; //返回映射表的元素个数
    // map operator[](key) => value  查询
    cout << map1[1000] << endl; 

    map1.erase(1020); // {1020, "王五" }删除了

    // 迭代器查询,迭代器查不到返回末尾的迭代器
	auto it1 = map1.find(1030);
	if (it1 != map1.end())
	{
		// it1 -> pair对象
		cout << "key:" << it1->first << " value:" << it1->second << endl;
	}


    return 0;
}