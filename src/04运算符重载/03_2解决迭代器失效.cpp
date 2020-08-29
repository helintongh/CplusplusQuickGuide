/*** 
 * @Author: helintongh
 * @Date: 2020-08-29 09:52:35
 * @LastEditTime: 2020-08-29 10:00:14
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/运算符重载/解决迭代器失效.cpp
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
    for ( int v : vec)
    {
        cout << v << " ";
    }
    cout << endl;

    // 把vec容器中所有的偶数全部删除
    auto it = vec.begin();
    for(; it != vec.end(); ) // 返回了新的iterator，当没有删除操作时才需要++it
    {
        if(*it % 2 == 0)
        {
            // 迭代器失效的问题，第一次调用erase以后，迭代器it就失效了
            // 注意和迭代器失效的代码比对
            // 通过返回新的iterator解决迭代器失效问题
            it = vec.erase(it); // insert(it, val) erase(it)
            //break; // 用break只删除一个运行正确,去掉break进程出现异常
        }
        else
        {
            ++it;
        }
    }

    for ( int v : vec)
    {
        cout << v << " ";
    }
    cout << endl;

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
            // 注意和迭代器失效的代码比对
            // 通过返回新的iterator解决迭代器失效问题
			it1 = vec1.insert(it1, *it1-1);
			++it1; // 碰到偶数在当前位置插入后,要往后走一步
			//break;
		}
	}
	return 0;
}
