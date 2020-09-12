/*** 
 * @Author: helintongh
 * @Date: 2020-09-12 08:47:41
 * @LastEditTime: 2020-09-12 08:58:28
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/多重继承/支持类型识别的转换.cpp
 */
#include <iostream>
using namespace std;
/*
C++语言级别提供的四种类型转换方式
int a = (int)b;
const_cast : 去掉（指针或者引用）常量属性的一个类型转换
static_cast :  提供编译器认为安全的类型转换（没有任何联系的类型之间的转换就被否定了）
reinterpret_cast : 类似于C风格的强制类型转换
dynamic_cast : 主要用在继承结构中，可以支持RTTI类型识别的上下转换
*/

class Base
{
public:
	virtual void func() = 0;
};
class Derive1 : public Base
{
public:
	void func() { cout << "call Derive1::func" << endl; }
};
class Derive2 : public Base
{
public:
	void func() { cout << "call Derive2::func" << endl; }
	// Derive2实现新功能的API接口函数,用基类函数统一调用该函数的办法? => dynamic_cast强制转换
	void derive02func() 
	{ 
		cout << "call Derive2::derive02func" << endl; 
	}
};
/*
typeid(*p).name() == "Derive" => 可以用if语句比较来执行derive02func
*/
// 基类指针统一指向派生类对象
void showFunc(Base *p)
{
	// dynamic_cast会检查p指针是否指向的是一个Derive2类型的对象？
	// p->vfptr->vftable RTTI信息 如果是，dynamic_cast转换类型成功，
	// 返回Derive2对象的地址，给pd2；否则返回nullptr
	// static_cast编译时期的类型转换  dynamic_cast运行时期的类型转换 支持RTTI信息识别
	Derive2 *pd2 = dynamic_cast<Derive2*>(p);
	if (pd2 != nullptr)
	{
		pd2->derive02func(); // 用pd2来调用该函数,p指针还不知它是指向谁
	}
	else
	{
		p->func(); // 动态绑定  *p的类型 Derive2  derive02func
	}
}
int main()
{
	Derive1 d1;
	Derive2 d2;
	showFunc(&d1);
	showFunc(&d2);
	return 0;
}
