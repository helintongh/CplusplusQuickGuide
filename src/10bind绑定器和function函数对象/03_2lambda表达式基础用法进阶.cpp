#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <map>
#include <memory>
#include <queue>

using namespace std;
/*
C++11 函数对象的升级版 => lambda表达式
函数对象的使用范围及缺点：
使用在泛型算法参数传递   比较性质/自定义操作  而如果函数对象用于 -> 优先级队列或智能指针 => 构造对象只用在一处
缺点在于: 如果你对该函数对象使用频率较低,仍需构造一个函数对象。不灵活

lambda表达式的语法：
[捕获外部变量](形参列表)->返回值{操作代码};

如果lambda表达式的返回值不需要，那么"->返回值"可以省略的

[捕获外部变量]
[]：表示不捕获任何外部变量
[=]：以传值的方式捕获外部的所有变量
[&]：以传引用的方式捕获外部的所有变量
[this]：捕获外部的this指针
[=,&a]：以传值的方式捕获外部的所有变量，但是a变量以传引用的方式捕获
[a, b]：以值传递的方式捕获外部变量a和b
[a, &b]：a以值传递捕获，b以传引用的方式捕获
*/
int main()
{
	vector<int> vec;
	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand() % 100 + 1);
	}

	sort(vec.begin(), vec.end(), 
		[](int a, int b)->bool
		{
			return a > b; // 从大到小
		});
	for (int val : vec)
	{
		cout << val << " ";
	}
	cout << endl;

	// 65按序插入序列  要找第一个小于65的数字
	auto it = find_if(vec.begin(), vec.end(), 
		[](int a)->bool {return a < 65; });
	if (it != vec.end())
	{
		vec.insert(it, 65);
	}
	for (int val : vec)
	{
		cout << val << " ";
	}
	cout << endl;

	for_each(vec.begin(), vec.end(), [](int a)->void
	{
		if(a % 2 == 0)
			cout << a << " ";
	});
	cout << endl;

	return 0;
}