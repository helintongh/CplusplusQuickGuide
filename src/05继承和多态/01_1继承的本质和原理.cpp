/*** 
 * @Author: helintongh
 * @Date: 2020-08-29 23:06:53
 * @LastEditTime: 2020-08-30 15:11:52
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/继承与多态/继承的本质和原理.cpp
 */
#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;
/*
1.继承的本质和原理
2.派生类的构造过程
3.重载、覆盖、隐藏
4.静态绑定和动态绑定
5.多态 vfptr和vftable
6.抽象类的设计原理
7.多重继承以及问题
8.虚基类 vbptr和vbtable
9.RTTI
10.C++四种类型强转
11.继承多态常见笔试面试题分享
*/

/*
1.继承的本质和原理
继承的本质：a.代码的复用  b.
类和类之间的关系：
组合：a part of... ...一部分的关系
继承：a kind of... ...一种的关系

注: 自己的成员变量自己是可以访问的(无论什么属性)，成员方法的访问限定也与下面相同

继承方式     基类的访问限定     派生类的访问限定      (main)外部的访问限定
public 
			  public			public                 Y
			  protected			protected			   N
			  private			不可见的				N

protected(基类的成员的访问限定，在派生类里面是不可能超过继承方式的)
			  public			protected			   N
			  protected			protected			   N
			  private			不可见的				N
              
private
			  public			private				   N
			  protected			private				   N
			  private			不可见的				N

总结：
1.外部只能访问对象public的成员，protected和private的成员无法直接访问
2.在继承结构中，派生类从基类可以继承过来private的成员，但是派生类却无法直接访问
3.protected和private的区别？在基类中定义的成员，想被派生类访问，但是不想被外部访问，
那么在基类中，把相关成员定义成protected保护的；如果派生类和外部都不打算访问，那么
在基类中，就把相关成员定义成private私有的。

默认的继承方式是什么？
要看派生类是用class定义的，还是struct定义的？
class定义派生类，默认继承方式就是private私有的
struct定义派生类，默认继承方式就是public私有的
*/

class A
{
public:
    int ma;
protected:
    int mb;
private:
    int mc; // 自己或者友元能访问私有的成员
};
//继承 A 基类/父类   B 派生类/子类
class B : public A // 如果B也需要ma,mb和mf继承A就可以了
{
public:
    void func()
    {
        cout << ma << endl;
        cout << mb << endl; // 公有继承,可访问派生类里的protected属性
    }
    int md;
protected:
    int me;
private:
    int mf;
};
class C : public B
{
	// 在C里面，请问ma的访问限定是什么？ 主要看在B里面ma是什么属性,如果在B里是私有的。那么就不可见的,但是能继承来
};
int main()
{
    B b;
	cout << b.ma << endl;

    return 0;
}