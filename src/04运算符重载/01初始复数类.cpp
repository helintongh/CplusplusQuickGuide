/*** 
 * @Author: helintongh
 * @Date: 2020-08-19 21:44:24
 * @LastEditTime: 2020-08-20 22:52:40
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/运算符重载/初始复数类.cpp
 */
#include <iostream>
using namespace std;

/*
C++的运算符重载：使对象的运算表现得和编译器内置类型一样
template<typename T>
T sum(T a, T b)
{
	return a+b; // a.operator+(b) , 对象和对象直接相加需要重载+号相当于a调用+法函数把b当作实参传入
}
复数类
*/
class CComplex
{
public:
    //
    CComplex(int r=0, int i=0)
        :mreal(r), mimage(i)  {}
    // 指导编译器怎么做CComplex类对象的加法操作
    CComplex operator+(const CComplex &src) // 返回对象的引用(&) 比 返回对象本身开销小。但无法返回局部变量的引用
    {
        // CComplex comp;
        // comp.mreal = this->mreal + src.mreal;
        // comp.mimage = this->mimage + src.mimage;
        // return comp;
        // 上述代码可以优化为
        return CComplex(this->mreal + src.mreal,
            this->mimage + src.mimage);
    }
    void show() { cout << "real:"<< mreal << " image:" << mimage << endl; }
private:
    int mreal;
    int mimage;

};

int main()
{
    CComplex comp1(10, 10);
    CComplex comp2(20, 20);
    //  comp1.operator+(comp2) 加法运算符的重载函数
    //  
    CComplex comp3 = comp1 + comp2; // =号后的语句可写为 comp1.operator+(comp2)
    comp3.show();

    CComplex comp4 = comp1 + 20; // comp1.operator+(20) int -> CComplex CComplex(int)
    comp4.show();

    return 0;

}

