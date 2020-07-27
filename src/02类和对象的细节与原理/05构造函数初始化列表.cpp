#include <iostream>
#include <cstring>
using namespace std;


/*
构造函数的初始化列表 ： 可以指定当前对象成员变量的初始化方式
CDate信息 是  CGoods商品信息的一部分  a part of...  组合的关系
*/

class CData; // 日期类

class CGoods
{
public:
	// “CDate”: 没有合适的默认构造函数可用,只能用自定义的
	CGoods(const char *n, int a, double p, int y, int m, int d) // 提供了带参数的构造,就不会自动生成默认构造了
		:_date(y, m, d) // CData _data(y, m, d); // 指定了日期对象的构造方式
		,_amount(a) // int _amount = a;
		,_price(p) // #1 构造函数的初始化列表
	{
		// #2 当前类类型构造函数体
		strcpy(_name, n);
        // _amount = a; // 相当于 int _amount; _amount = a; 有两步
        // _data = CData(y, m, d); // 出错,CData _data;没有默认构造这一步出错
    }
	void show()
	{
		cout << "name:" << _name << endl;
		cout << "amount:" << _amount << endl;
		cout << "price:" << _price << endl;
		_date.show();
	}
private:
	char _name[20];
	int _amount;
	double _price;
	CDate _date;  // 成员对象  1.分配内存  2.调用构造函数 => 达成了CData和CGoods的组合
};

/*
日期类
*/
class CDate
{
public:
	CDate(int y, int m, int d) // 自定义了一个构造函数，编译器就不会再产生默认构造了
	{
		_year = y;
		_month = m;
		_day = d;
	}
	void show()
	{
		cout << _year << "/" << _month << "/" << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};

int main()
{
    CGoods good("商品", 100, 35.0, 2019, 5, 12);
    good.show();

    return 0;
}