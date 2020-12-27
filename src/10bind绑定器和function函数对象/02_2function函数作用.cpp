#include <iostream>
#include <vector> 
#include <map>
#include <functional>  // 使用function函数对象类型
#include <algorithm>
#include <ctime>
#include <string>
using namespace std;

/*
C++11提供的绑定器和函数对象
          bind   function
		  C++ STL  bind1st和bind2nd =》 本身还是一个函数对象
function : 绑定器，函数对象，lambda表达式 它们只能使用在一条语句中
*/

void doShowAllBooks() { cout << "查看所有书籍信息" << endl; }
void doBorrow() { cout << "借书" << endl; }
void doBack() { cout << "还书" << endl; }
void doQueryBooks() { cout << "查询书籍" << endl; }
void doLoginOut() { cout << "注销" << endl; }
// 实现一个菜单功能
int main()
{
	int choice = 0;
	//       C的函数指针
	map<int, function<void()>> actionMap; // 这里键对应的是函数对象
	actionMap.insert({ 1, doShowAllBooks }); // insert(make_pair(xx,xx));
	actionMap.insert({ 2, doBorrow });
	actionMap.insert({ 3, doBack });
	actionMap.insert({ 4, doQueryBooks });
	actionMap.insert({ 5, doLoginOut });

	for (;;)
	{
		cout << "-----------------" << endl;
		cout << "1.查看所有书籍信息" << endl;
		cout << "2.借书" << endl;
		cout << "3.还书" << endl;
		cout << "4.查询书籍" << endl;
		cout << "5.注销" << endl;
		cout << "-----------------" << endl;
		cout << "请选择:";
		cin >> choice;

		auto it = actionMap.find(choice); // map  pair  first second
		if (it == actionMap.end()) // 不存在该选项
		{
			cout << "输入数字无效，重新选择!" << endl;
		}
		else
		{
			it->second();
		}
		// 不好,因为这块代码无法闭合  无法做到 开-闭原则
		/*switch (choice)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		default:
			break;
		}*/
	}

	return 0;
}