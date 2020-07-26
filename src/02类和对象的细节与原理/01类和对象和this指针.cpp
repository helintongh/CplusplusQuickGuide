#include <iostream>
#include <cstring>

using namespace std; // std::cout std::endl

/*
C++ OOP面向对象   OOP编程，this指针
C： 各种各样的函数的定义  struct
C++：类   =>  实体的抽象类型
实体（属性、行为） ->  ADT(abstract data type)
 |                            |
对象			  <-(实例化) 类（属性->成员变量  行为->成员方法）

OOP语言的四大特征是什么？
抽象    封装/隐藏    继承    多态

类 -> 商品实体
访问限定符：public公有的 private私有的 protected保护的
*/
const int NAME_LEN = 20;
class CGoods  // => 商品的抽象数据类型
{
public: // 给外部提供公有的成员方法，来访问私有的属性
	// 做商品数据初始化用的  
	void init(const char *name, double price, int amount);
	// 打印商品信息
	void show();
	// 给成员变量提供一个getXXX或setXXX的方法 类体内实现的方法，自动处理成inline内联函数
	void setName(char *name) { strcpy(_name, name); }
	void setPrice(double price) { _price = price; }
	void setAmount(int amount) { _amount = amount; }

	const char* getName() { return _name; } // 如果返回普通char*则外部可以拿到私有成员变量的值
	double getPrice() { return _price; }
	int getAmount() { return _amount; }
private: // 属性一般都是私有的成员变量
	char _name[NAME_LEN]; //  20字节 对齐=>24
	double _price;  // 8字节 谁类型最长按照谁对齐
	int _amount; // 4字节 对齐=> 8字节
};
void CGoods::init(const char *name, double price, int amount)
{
	strcpy(this->_name, name); // 实际上不加this也可以,编译器会自动添加
	this->_price = price;
	this->_amount = amount;
}
void CGoods::show()
{
	cout << "name:" << this->_name << endl;
	cout << "price:" << this->_price << endl;
	cout << "amount:" << this->_amount << endl;
}
int main()
{
	/*
	CGoods可以定义无数的对象，每一个对象都有自己的成员变量
	但是它们共享一套成员方法

	show() => 怎么知道处理哪个对象的信息？
	init(name, price, amount) => 怎么知道把信息初始化给哪一个对象的呢？
	
	类的成员方法一经编译，所有的方法参数，都会加一个this指针，接收
	调用该方法的对象的地址
    在上述代码中比如void setName(char *name)实际上是void setName(CGoods *this, char *name)
	*/
	
	// 对象内存大小的时候  对象的内存大小 => 只和成员变量有关
	CGoods good1; // 类实例化了一个对象
    // 实际调用还传入了good1
	// init(&good1, "面包", 10.0, 200) 
	good1.init("面包", 10.0, 200);
	// show(&good1)
	good1.show();

	good1.setPrice(20.5); // 改变面包的单价
	good1.setAmount(100); // 改变面包库存
	good1.show();

	CGoods good2;// 类实例化了一个对象
	good2.init("空调", 10000.0, 50);
	good2.show();

    return 0; 
}