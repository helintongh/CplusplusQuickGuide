/*** 
 * @Author: helintongh
 * @Date: 2020-09-05 19:51:04
 * @LastEditTime: 2020-09-05 20:21:08
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/继承与多态/理解多态.cpp
 */
#include <iostream>
#include <string>
using namespace std;
/*
如何解释多态？ 
静态（编译时期）的多态： 函数重载、模板（函数模板和类模板）
bool compare(int, int){}
bool compare(double, double){} 

compare(10, 20); call compare_int_int 在编译阶段就确定好调用的函数版本
compare(10.5, 20.5); call compare_douoble_double 在编译阶段就确定好调用的函数版本

template<typename T>
bool compare(T a, T b){}

compare<int>(10, 20);  => int 实例化一个 compare<int>
compare(10.5, 20.5); => double 实例化一个 compare<double>

动态（运行时期）的多态：   Base Derive
在继承结构中，基类指针（引用）指向派生类对象，通过该指针（引用）调用同名覆盖方法（虚函数）
，基类指针指向哪个派生类对象，就会调用哪个派生类对象的同名覆盖方法，称为多态
 pbase->bark();
 多态底层是通过动态绑定来实现的，pbase->访问谁的vfptr=>继续访问谁的vftable
                                =>当然调用的是对应的派生类对象的方法了


继承的好处是什么？
1.可以做代码的复用
2.在基类中给所有派生类提供统一的虚函数接口，让派生类进行重写，然后就可以使用多态了
*/

// 动物的基类
class Animal
{
public:
	Animal(string name) :_name(name) {}
	virtual void bark() {}
protected:
	string _name;
};
// 以下是动物实体类
class Cat : public Animal
{
public:
	Cat(string name) :Animal(name) {}
	void bark() { cout << _name << " bark: miao miao!" << endl; }
};
class Dog : public Animal
{
public:
	Dog(string name) :Animal(name) {}
	void bark() { cout << _name << " bark: wang wang!" << endl; }
};
class Pig : public Animal
{
public:
	Pig(string name) :Animal(name) {}
	void bark() { cout << _name << " bark: heng heng!" << endl; }
};
/*
下面的一组bark API接口无法做到我们软件涉及要求的“开-闭“原则
软件设计由六大原则   “开-闭“原则  对修改关闭，对扩展开放

void bark(Cat &cat) { cat.bark();} // 添加一种动物就要新加代码,屏蔽一种动物就要删除代码
void bark(Dog &dog) { dog.bark();}
void bark(Pig &pig) { pig.bark();}
*/
// 用统一的基类对象来接收派生类对象
void bark(Animal *p)
{
	p->bark(); // Animal::bark虚函数，动态绑定了 
	/*
	p->cat Cat vftable &Cat::bark
	p->dog Dog vftable &Dog::bark
	p->pig Pig vftable &Pig::bark
	*/
}

int main()
{
	Cat cat("猫咪");
	Dog dog("二哈");
	Pig pig("佩奇");

	bark(&cat);
	bark(&dog);
	bark(&pig);

	return 0;
}