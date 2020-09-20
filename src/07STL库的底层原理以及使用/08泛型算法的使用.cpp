/*** 
 * @Author: helintongh
 * @Date: 2020-09-20 17:45:28
 * @LastEditTime: 2020-09-20 18:01:06
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/STL库/泛型算法的使用.cpp
 */
#include <iostream>
#include <vector>
#include <algorithm> // 包含了C++ STL里面的泛型算法
#include <functional> // 包含了函数对象和绑定器
using namespace std;

/*
五、泛型算法 = template + 迭代器 + 函数对象
特点一：泛型算法的参数接收的都是迭代器
特点二：泛型算法的参数还可以接收函数对象（C函数指针）
sort,find,find_if,binary_search,for_each

绑定器 + 二元函数对象 => 一元函数对象
bind1st：把二元函数对象的operator()(a, b)的第一个形参绑定起来
bind2nd：把二元函数对象的operator()(a, b)的第二个形参绑定起来
*/
int main()
{
	int arr[] = { 12,4,78,9,21,43,56,52,42,31};
	vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));

	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;

	// 默认小到大的排序
	sort(vec.begin(), vec.end());

	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;

	// 有序容器中进行二分查找效率很高,返回值是bool值
	if (binary_search(vec.begin(), vec.end(), 21)) 
	{
		cout << "binary_search 查找的值存在" << endl;
	}
	// find的使用,找不到返回end()
	auto it1 = find(vec.begin(), vec.end(), 21);
	if (it1 != vec.end())
	{
		cout << "find 21存在" << endl;
	}
	
	// 传入函数对象greater，改变容器元素排序时的比较方式
	sort(vec.begin(), vec.end(), greater<int>()); // 从大到小
	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;

	// 78 56 52 43 42 31 21 12 9 4
	// 需求:
	// 把48按序插入到vector容器当中  找第一个小于48的数字
	// 按上面的需求 => find_if需要的是一个一元函数对象(只有一个参数)
	// greater a > b    less a < b(48) =>用greater把a绑定为48用bind1st    用less把b绑定为48用bind2nd
	/*
	auto it2 = find_if(vec.begin(), vec.end(),
		bind1st(greater<int>(), 48));
	// 下面是lambda表达式与上述代码相同
	*/
	auto it2 = find_if(vec.begin(), vec.end(),
		//bind1st(greater<int>(), 48));
		//bind2nd(less<int>(), 48));
		[](int val)->bool {return val < 48; });
	vec.insert(it2, 48);
	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;

	// for_each可以遍历容器的所有元素，可以自行添加合适的函数对象对容器
	// 的元素进行过滤
	for_each(vec.begin(), vec.end(), 
		[](int val)->void
	{
		if (val % 2 == 0)
		{
			cout << val << " ";
		}
	});
	cout << endl;

	return 0;
}