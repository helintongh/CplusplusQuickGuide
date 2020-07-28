#include <iostream>
#include <cstring>
using namespace std;

/*
类的各种成员 - 成员方法/变量

普通的成员方法 => 编译器会添加一个this形参变量
1.属于类的作用域
2.调用该方法时，需要依赖一个对象(常对象是无法调用的 实参:const CGoods*   CGoods *this)
3.可以任意访问对象的私有成员   protected继承  public private

static静态成员方法 => 不会生成this形参
1.属于类的作用域
2.用类名作用域来调用方法
3.可以任意访问对象的私有成员，仅限于不依赖对象的成员（只能调用其它的static静态成员）

const常成员方法 => const CGoods *this
1.属于类的作用域
2.调用依赖一个对象，普通对象或者常对象都可以
3.可以任意访问对象的私有成员，但是只能读，而不能写
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
	void show()const
	{
		cout << _year << "/" << _month << "/" << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};

/*
构造函数的初始化列表 ： 可以指定当前对象成员变量的初始化方式
CDate信息   CGoods商品信息的一部分  a part of...  组合的关系
*/
class CGoods
{
public:
	// “CDate”: 没有合适的默认构造函数可用
	CGoods(const char *n, int a, double p, int y, int m, int d)
		:_date(y, m, d)
		, _amount(a) // int _amount = a;
		, _price(p) // #1 构造函数的初始化列表
	{
		// #2 当前类类型构造函数体
		strcpy(_name, n);
		_count++; // 记录所有产生的新对象的数量
	}
	// 普通成员方法
	void show() // 打印商品的私有的信息 CGoods *this
	{
		cout << "name:" << _name << endl;
		cout << "amount:" << _amount << endl;
		cout << "price:" << _price << endl;
		_date.show();
	}
	// 常成员方法  只要是只读操作的成员方法，一律实现成const常成员方法
	void show()const // const CGoods *this
	{
		cout << "name:" << _name << endl;
		cout << "amount:" << _amount << endl;
		cout << "price:" << this->_price << endl;
		_date.show();
	}
	// 静态成员方法 没有this指针的
	static void showCGoodsCount() // 打印的是所有商品共享的信息,不加static必须要good.showCGoodsCount()
	{
		cout << "所有商品的种类数量是：" << _count << endl;
	}
private:
	char _name[20];
	int _amount;
	double _price;
	CDate _date;  // 成员对象  1.分配内存  2.调用构造函数
	static int _count; // static声明->不属于对象，而是属于类级别的 声明 用来记录商品对象的总数量
};

// static成员变量一定要在类外进行定义并且初始化
int CGoods::_count = 0;
int main()
{
	CGoods good1("商品1", 100, 35.0, 2019, 5, 12);
	good1.show();

	CGoods good2("商品2", 100, 35.0, 2019, 5, 12);
	good2.show();

	CGoods good3("商品3", 100, 35.0, 2019, 5, 12);
	good3.show();

	CGoods good4("商品4", 100, 35.0, 2019, 5, 12);
	good4.show();

	// 统计所有商品的总数量
	CGoods::showCGoodsCount();
    // 不能修改的const修饰,普通方法常量对象无法调用
	const CGoods good5("非卖品商品5", 100, 35.0, 2019, 5, 12);
	good5.show(); // CGoods::show(&good5)  const CGoods*  -> const CGoods *this

	return 0;
}
