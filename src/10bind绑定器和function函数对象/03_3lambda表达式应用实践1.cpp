#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <map>
#include <memory>
#include <queue>
using namespace std;
/*
既然lambda表达式只能使用在语句当中，如果想跨语句使用之前定义好的lambda表达式，
怎么办？用什么类型来表示lambda表达式？
当然是用function类型来表示函数对象的类型了   bind1st/bind2nd bind绑定器

lambda表达式 => 函数对象   
*/

int main()
{
	// 1.lambda表达式存放到map中
	map<int, function<int(int, int)>> caculateMap;
	caculateMap[1] = [](int a, int b)->int {return a + b; };
	caculateMap[2] = [](int a, int b)->int {return a - b; };
	caculateMap[3] = [](int a, int b)->int {return a * b; };
	caculateMap[4] = [](int a, int b)->int {return a / b; };

	cout << "选择:";
	int choice;
	cin >> choice;
	cout << "10 + 15:" << caculateMap[choice](10, 15) << endl;

	// 智能指针自定义删除器   delete p;  FILE*   fclose(FILE*)
	// unique_ptr<FILE> ptr(fopen("data.txt"), "w");
	// 上面需要自定义函数对象进行fclose操作,默认操作是delete
	/*
	unique_ptr<FILE, function<void(FILE*)>> 
		ptr1(fopen("data.txt", "w"), [](FILE *pf)->void {fclose(pf); });
	*/
	return 0;
}