/*** 
 * @Author: helintongh
 * @Date: 2020-09-06 10:46:03
 * @LastEditTime: 2020-09-06 10:56:55
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/继承与多态/继承多态笔试题2.cpp
 */
#include <iostream>
using namespace std;
class Base
{
public:
    virtual void show(int i = 10)
    {
        cout << "call Base::show i:" << i << endl;
    }
};

class Derive : public Base
{
public:
    void show(int i = 20) // 覆盖关系
    {
        cout << "call Derive::show i:" << i << endl;
    }
};

int main()
{

    Base *p = new Derive(); // 虚析构函数
    /* 下面的OUTPUT为:
            call Derive::show i:10
        编译阶段编译器只能看到Base::show,压入栈的是Base::show的默认值10
    */
    /*
	push 0Ah => 函数调用，参数压栈是在编译时期就确定好的
	mov eax, dword ptr[p]
	mov ecx, dword ptr[eax]
	call ecx
	*/
    p->show();  // 动态绑定 p-> Derive vfptr -> Derive vftable
    delete p;
 
    return 0;
}


