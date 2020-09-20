/*** 
 * @Author: helintongh
 * @Date: 2020-09-20 13:08:19
 * @LastEditTime: 2020-09-20 13:12:11
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/STL库/有序关联容器之集合.cpp
 */
#include <iostream>
#include <cstdlib>
// 使用无序关联容器包含的头文件
#include <unordered_set>
#include <unordered_map>

// 使用有序关联容器包含的头文件  红黑树
#include <set> // set multiset
#include <map> // map multimap
using namespace std;

int main()
{
    set<int> set1;
    for(int i = 0; i < 20; ++i)
    {
        set1.insert(rand()%20 + 1);
    }

    for(int v : set1)
    {
        cout << v << " "; // 单重集合,不会重复存储,从小到大排列(红黑树中序遍历)
    }
    cout << endl;

    return 0;
}