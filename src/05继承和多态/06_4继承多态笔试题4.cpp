/*** 
 * @Author: helintongh
 * @Date: 2020-09-06 11:24:32
 * @LastEditTime: 2020-09-06 11:55:09
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/继承与多态/继承多态笔试题4.cpp
 */
#include <iostream>
#include <cstring>
using namespace std;
class Base
{
public:
	Base()
	{
		/*
		push ebp
		mov ebp, esp
		sub esp, 4Ch
		rep stos esp<->ebp 0xCCCCCCCC(GCC/G++编译器不做此步操作)
		vfptr <- &Base::vftable (虚函数表里写入vfptr)
		*/
		cout << "call Base()" << endl;
		clear(); // 把vfptr的值清空为0
	}
	void clear() { memset(this, 0, sizeof(*this)); }
	virtual void show()
	{
		cout << "call Base::show()" << endl;
	}
};
class Derive : public Base
{
public:
	Derive()
	{
		/*
		push ebp
		mov ebp, esp
		sub esp, 4Ch
		rep stos esp<->ebp 0xCCCCCCCC(windows VS GCC/G++)
		vfptr <- &Derive::vftable
		*/
		cout << "call Derive()" << endl;
	}
	void show()
	{
		cout << "call Derive::show()" << endl;
	}
};
int main()
{
    // 第一段报错
#if 0    
	Base *pb1 = new Base();
	/*
	mov eax, dword ptr[pb1]
	mov ecx, dword ptr[eax] eax:0x00000000 不是Base::vftable
	call ecx
	*/
	pb1->show(); // 动态绑定
	delete pb1;
#endif

	Base *pb2 = new Derive();
	// 动态绑定 call Derive::show()
	/*
	vfptr里面存储的是vftable的地址
	vfptr <- vftable
	*/
	pb2->show(); 
	delete pb2;

	return 0;
}