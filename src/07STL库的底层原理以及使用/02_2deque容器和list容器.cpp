/*** 
 * @Author: helintongh
 * @Date: 2020-09-12 21:56:33
 * @LastEditTime: 2020-09-13 14:43:46
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/deque容器和list容器.cpp
 */
#include <iostream>
#include <deque>
#include <list>
using namespace std;
/*
deque：双端队列容器
底层数据结构：动态开辟的二维数组，一维数组从2开始，以2倍的方式进行扩容，每次扩容后，原来第二维的数组，从
新的第一维数组的下标oldsize/2开始存放，上下都预留相同的空行，方便支持deque的首尾元素添加

deque<int> deq;
增加：
deq.push_back(20); 从末尾添加元素 O(1)  
deq.push_front(20); 从首部添加元素 O(1)   // vec.insert(vec.begin(), 20) O(n)
deq.insert(it, 20); it指向的位置添加元素 O(n)

删除：
deq.pop_back(); 从末尾删除元素 O(1)  
deq.pop_front(); 从首部删除元素 O(1)  
deq.erase(it);  从it指向的位置删除元素 O(n)

查询搜索：
iterator(连续的insert和erase一定要考虑迭代器失效的问题)
deq.back(); 获取尾部元素 0(1)

list：链表容器
底层数据结构：双向的循环链表   pre data next
list<int> mylist;
增加：
mylist.push_back(20); 从末尾添加元素 O(1)
mylist.push_front(20); 从首部添加元素 O(1)   // vec.insert(vec.begin(), 20) O(n)
mylist.insert(it, 20); it指向的位置添加元素 O(1) // 链表中进行insert的时候，先要进行一个query查询操作
    对于链表来说，查询操作效率就比较慢了(从头节点一个一个遍历)

删除：
mylist.pop_back(); 从末尾删除元素 O(1)
mylist.pop_front(); 从首部删除元素 O(1)
mylist.erase(it);  从it指向的位置删除元素 O(1)

查询搜索：
iterator(连续的insert和erase一定要考虑迭代器失效的问题)

deque和list，比vector容器多出来的增加删除函数接口：
push_front和pop_front
*/
int main()
{
    
}