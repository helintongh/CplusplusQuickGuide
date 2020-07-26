#include <iostream>
#include <typeinfo>
using namespace std;

/*
const，一级指针，引用的结合
*/

int main()
{
    // 写一句代码,在内存的0x0018ff44处写一个4字节的10
    // int *p = (int*)0x0018ff44; // 正确
    // *p = 10;
    //int *&&p = (int*)0x0018ff44; // 正确
   // int *const &p = (int*)0x0018ff44; // 正确

    int a = 10;
    int *p = &a;
    //int **q = &p; // 正确
    int *&q = p; // 正确 与上面等价
    /*
        错误,无法判断还原为指针再判断
        可以使用typeid(q).name()看一下,引用是不参与类型的
    */
    //const int *&q = p; 
    // const int*    p的类型是: int*
    /*
        与上面等价,
        错误const与二级指针结合要么左右两边都有const,要么都没有不能出现一边有一边没有
    */
    //const int **q = &p; 


    /* 选择题
        正确
        int a = 10;
        int *p = &a;
        int *&q = p; // int **q = &p; // int ** <= int **

        错误
        int a = 10;
        int *p = &a;
        const int *&q = p;
        const int **q = &p; //const int** <= int** 

        错误
        int a = 10;
        const int *p = &a;
        int *&q = p;
        int **q = &p; // int** <= const int**

        错误
        int a = 10;
        int *const p = &a; // p是常量,不能把常量地址泄漏给普通指针
        int *&q = p; 
        int **q = &p; // *q =  *q赋值就改变了p
    */
	return 0;
}