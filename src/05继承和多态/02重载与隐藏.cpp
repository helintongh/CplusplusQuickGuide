/*** 
 * @Author: helintongh
 * @Date: 2020-08-30 15:27:12
 * @LastEditTime: 2020-08-30 16:07:34
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/继承与多态/重载与隐藏.cpp
 */

#include <iostream>
using namespace std;
/*
重载、隐藏、覆盖
1.重载关系
一组函数要重载，必须处在同一个作用域当中；而且函数名字相同，参数列表不同

2.隐藏(作用域的隐藏)的关系
在继承结构当中，派生类的同名成员，把基类的同名成员给隐藏调用了


============================================================
1.把继承结构，也说成从上（基类）到下（派生类）的结构

2.
基类对象 -> 派生类对象
派生类对象 -> 基类对象

基类指针（引用）-> 派生类对象
派生类指针（引用）-> 基类对象

总结：在继承结构中进行上下的类型转换，默认只支持从下(派生类)到上(基类)的类型的转换 OK
如下是可行的:
    Base b(10); // 基类
	Derive d(20); // 派生类
    b = d;
    Base *pb = &d;
*/
class Base
{
public:
	Base(int data = 10) :ma(data) {}
	void show() { cout << "Base::show()" << endl; } //#1
	void show(int) { cout << "Base::show(int)" << endl; }//#2
protected:
	int ma;
};
class Derive : public Base
{
public:
	Derive(int data = 20) :Base(data), mb(data) {}
	void show() { cout << "Derive::show()" << endl; } //#3
private:
	int mb;
};
int main()
{

// 1.重载和隐藏
#if 0
	Derive d;
	d.show();
	d.Base::show();
    // d.show(10)会报如下错误
	//“Derive::show”: 函数不接受 1 个参数
	d.Base::show(10); // 指定基类作用域来调用基类的成员函数
	d.show(20);//优先找的是派生类自己作用域的show名字成员；没有的话，才去基类里面找。=> 这句会出错
#endif

// 基类到派生类对象的转换
#if 1
	Base b(10);
	Derive d(20);
    // 可以理解为基类是人,派生类是学生。你需要人，给你一个学生也可
	// 基类对象b <- 派生类对象d   类型从下到上的转换  Y
	b = d;

	// 派生类对象d <- 基类对象b   类型从上到下的转换  N
	// d = b;

	// 基类指针（引用）<- 派生类对象  类型从下到上的转换 Y
	Base *pb = &d; // 只能访问派生类继承基类的部分,指针的类型限制指针解引用的能力
	pb->show();
	//((Derive*)pb)->show(); // 这是强制使用派生类的成员方法
	pb->show(10);

	// 派生类指针（引用）<- 基类对象  类型从上到下的转换  N
	Derive *pd = (Derive*)&b; // 不安全，涉及了内存的非法访问！
	pd->show();
#endif
	return 0;
}