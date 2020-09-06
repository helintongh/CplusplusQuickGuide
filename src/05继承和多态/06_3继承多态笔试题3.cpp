/*** 
 * @Author: helintongh
 * @Date: 2020-09-06 10:58:05
 * @LastEditTime: 2020-09-06 11:17:26
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/继承与多态/继承多态笔试题3.cpp
 */
#include <iostream>
using namespace std;
class Base
{
public:
    virtual void show()
    {
        cout << "call Base::show" << endl;
    }
};

class Derive : public Base
{
private:
    void show() 
    {
        cout << "call Derive::show" << endl;
    }
};
// 基类方法公有,派生类私有,声明一个基类指针指向派生类能否调用派生类的私有方法
int main()
{
    Base *p = new Derive();
    /*
	成员方法能不能调用，就是说方法的访问权限是不是public的，
    是在编译阶段就需要确定好的

	编译阶段(只能看到) Base::show -> 引申:如果基类是私有的,派生类是公有就无法访问。编译阶段报错
	call Base::show   call ecx
	*/
    p->show(); // 最终能调用到Derive::show,是在运行时期才确定的
    /*
    为什么可以访问?是因为指令发生了动态绑定,
    调用时访问了虚函数表
    */
    delete p;

 
    return 0;
}
