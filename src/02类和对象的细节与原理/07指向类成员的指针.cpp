#include <iostream>
using namespace std;

/*
指向类成员(成员变量和成员方法)的指针
*/
class Test
{
public:
	void func() { cout << "call Test::func" << endl; }
	static void static_func() { cout << "Test::static_func" << endl; }

	int ma; // 普通成员变量
	static int mb; // 静态成员变量
};
int Test::mb;
int main()
{

    // 1. 指向成员变量的指针

    // int a = 10; int *p = &a; *p = 30;
    //无法从“int Test::* ”转换为“int *”
    // int *p = &Test::ma; // 不知道说的是哪一个对象的ma
    // int Test::*p = &Test::ma; //也出错
    // *p = 20; // 出错

    Test t1;
    Test *t2 = new Test();

    int Test::*p = &Test::ma;
    t1.*p = 20; // 指明对象才能修改
    cout << t1.*p << endl;

    t2->*p = 30;
    cout << t2->*p << endl;

    int *p1 = &Test::mb; //mb是静态成员变量
    *p1 = 40;
    cout << *p1 << endl;

    // 2. 指向成员方法的指针

    // 无法从“void (__thiscall Test::* )(void)”转换为“void (__cdecl *)(void)”
    // void (*pfunc) () = &Test::func; 出错

    void (Test::*pfunc) () = &Test::func;
    (t1.*pfunc) ();
    (t2->*pfunc) ();

    // 如何定义函数指针指向类的static成员方法呢？
    void (*spfunc) () = &Test::static_func;
    (*spfunc) ();
    

    delete t2;
    return 0;
}