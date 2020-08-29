/*** 
 * @Author: helintongh
 * @Date: 2020-08-25 22:25:16
 * @LastEditTime: 2020-08-25 22:42:20
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/运算符重载/迭代器失效问题.cpp
 */

#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

/*
迭代器的失效问题？
1.迭代器为什么会失效？
a：当容器调用erase方法后，当前位置到容器末尾元素的所有的迭代器全部失效了
b：当容器调用insert方法后，当前位置到容器末尾元素的所有的迭代器全部失效了
     迭代器依然有效    迭代器全部失效
首元素   ->  插入点/删除点  ->  末尾元素

c：insert来说，如果引起容器内存扩容
   原来容器的所有的迭代器就全部失效了
首元素   ->  插入点/删除点  ->  末尾元素

d：不同容器的迭代器是不能进行比较运算的

2.迭代器失效了以后，问题该怎么解决？
对插入/删除点的迭代器进行更新操作

*/
int main()
{
    // 1.场景1
    vector<int> vec;
    for(int i = 0; i < 20; ++i)
    {
        vec.push_back(rand() % 100 + 1);
    }

    // 把vec容器中所有的偶数全部删除
    auto it = vec.begin();
    for(; it != vec.end(); ++it)
    {
        if(*it % 2 == 0)
        {
            // 迭代器失效的问题，第一次调用erase以后，迭代器it就失效了
            vec.erase(it); // insert(it, val) erase(it)
            //break; // 用break只删除一个运行正确,去掉break进程出现异常
        }
    }

    // 2. 场景2
    vector<int> vec1;
    for(int i = 0; i < 20; ++i)
    {
        vec1.push_back(rand() % 100 + 1);
    }
    // 给vec容器中所有的偶数前面添加一个小于偶数值1的数字
	auto it1 = vec1.begin();
	for (; it1 != vec1.end(); ++it1)
	{
		if (*it1 % 2 == 0)
		{
			// 这里的迭代器在第一次insert之后，iterator就失效了
			vec1.insert(it1, *it1-1);
			//++it1;
			//break;
		}
	}
	return 0;
}
