/*** 
 * @Author: helintongh
 * @Date: 2020-09-12 09:00:24
 * @LastEditTime: 2020-09-12 09:01:30
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/STL库/STL库分模块概述.cpp
 */

/*
C++ STL standard template libaray 标准模板库
一、标准容器 C++11 array  forward_list
1.顺序容器 
vector
deque
list
2.容器适配器
stack
queue
priority_queue(大根堆实现的)
3.关联容器 
无序关联容器 => 链式哈希表  增删查O(1) 
set:集合 key   map:映射表 [key,value]
unordered_set 单重集合
unordered_multiset 多重集合
unordered_map 单重映射表
unordered_multimap 多重映射表

有序关联容器 => 红黑树 增删查O(log2n) 2是底数(树的层数，树的高度)
set
multiset
map
multimap

二、近容器
数组，string，bitset(位容器)

三、迭代器
iterator和const_iterator
reverse_iterator和const_reverse_iterator

四、函数对象（类似C的函数指针）
greater,less

五、泛型算法
sort,find,find_if,binary_search,for_each
*/