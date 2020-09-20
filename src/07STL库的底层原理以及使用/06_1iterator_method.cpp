/*** 
 * @Author: helintongh
 * @Date: 2020-09-20 13:33:47
 * @LastEditTime: 2020-09-20 16:39:35
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/STL库/iterator_method.cpp
 */
#include <iostream>
#include <vector>
using namespace std;

/*
容器的迭代器
iterator:普通的正向迭代器 => 打印元素从第一个到最后一个,并且可以修改迭代器所指向的值
const_iterator:常量的正向迭代器  只能读，而不能写了
reverse_iterator:普通的反向迭代器
const_reverse_iterator:常量的反向迭代器
*/
int main()
{
    // 1. iterator普通的正向迭代器的基本使用
    vector<int> vec;
	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand() % 100);
	}

    //vector<int>::iterator it1 = vec.begin();
    auto it1 = vec.begin(); // auto来减少代码量
    for(; it1 != vec.end(); ++it1)
    {
        cout << *it1 << " ";
        if(*it1 %2 == 0)
        {
            *it1 = 0;
        }
    }
    cout << endl;

    for(int v : vec)
    {
        cout << v << " ";
    }



    return 0;
}