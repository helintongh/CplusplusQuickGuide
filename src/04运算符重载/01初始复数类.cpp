/*** 
 * @Author: helintongh
 * @Date: 2020-08-19 21:44:24
 * @LastEditTime: 2020-08-23 15:56:19
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
    // CComplex() CComplex(20) CComplex(30, 30) => 构造函数要保证构造三种不同的对象
    CComplex(int r=0, int i=0)
        :mreal(r), mimage(i)  {}
    // 指导编译器怎么做CComplex类对象的加法操作
    CComplex operator+(const CComplex &src) // 返回对象的引用(&) 比 返回对象本身开销小。但无法返回局部变量的引用,所以这里不能CComplex &operator
    {
        // CComplex comp;
        // comp.mreal = this->mreal + src.mreal;
        // comp.mimage = this->mimage + src.mimage;
        // return comp;
        // 上述代码可以优化为
        return CComplex(this->mreal + src.mreal,
            this->mimage + src.mimage);
    }
    CComplex operator++(int)
	{
		//CComplex comp = *this;
		//mreal += 1;
		//mimage += 1;
		//return comp;
        //上述逻辑可以优化为以下
		return CComplex(mreal++, mimage++);
	}
	CComplex& operator++()
	{
		mreal += 1;
		mimage += 1;
		return *this; // 返回操作后的本身
	}
    void operator+=(const CComplex &src)
    {
		mreal += src.mreal;
		mimage += src.mimage;
    }
    void show() { cout << "real:"<< mreal << " image:" << mimage << endl; }

private:
    int mreal;
    int mimage;

    friend CComplex operator+(const CComplex &lhs, const CComplex &rhs);
    friend ostream& operator<<(ostream &out, const CComplex &src);
	friend istream& operator>>(istream &in, CComplex &src);
};

CComplex operator+(const CComplex &lhs, const CComplex &rhs)
{
	return CComplex(lhs.mreal + rhs.mreal, lhs.mimage + rhs.mimage);
}
ostream& operator<<(ostream &out, const CComplex &src)
{
	out << "mreal:" << src.mreal << " mimage:" << src.mimage << endl;
	return out;
}
istream& operator>>(istream &in, CComplex &src)
{
	in >> src.mreal >> src.mimage;
	return in;
}
int main()
{
    CComplex comp1(10, 10);
    CComplex comp2(20, 20);
    //  comp1.operator+(comp2) 加法运算符的重载函数
    //  
    CComplex comp3 = comp1 + comp2; // =号后的语句可写为 comp1.operator+(comp2)
    comp3.show();
    // 20和comp1相加,没有问题
    CComplex comp4 = comp1 + 20; // comp1.operator+(20) int -> CComplex CComplex(int) 
    comp4.show();
    // 编译器做对象运算的时候，会调用对象的运算符重载函数（优先调用成员方法）；如果没有成员方法
	// ，就在全局作用域找合适的运算符重载函数(定义全局方法或者说友元方法)
	//            ::operator+(30, comp1)
    // 注:编译器优先找成员方法再匹配全局的方法
    CComplex comp5 = 30 + comp1; // 这里不可以,编译器没有理由把整型转换为CComplex类型。需要定义一个全局方法
    comp5.show();

    // 实现++操作
    // CComplex operator++(int) 前置++返回+之前的值
	comp5 = comp1++; // ++ --单目运算符  operator++() 前置++  operator++(int) 后置++
	comp1.show();
	comp5.show();
	// CComplex operator++()
	comp5 = ++comp1;
	comp1.show();
	comp5.show();

    // void comp1.operator+=(comp2)   ::operator+=(comp1, comp2)
	comp1 += comp2;
    comp1.show();
    //comp1.show(); // 对象信息的输出还可以重载<<和>>。函数需要返回值而且最好为全局函数
	//cout ::operator<<(cout, comp1)   void << endl;
	//ostream& operator<<(ostream &out, const CComplex &src) 注:流对象不要加const
	cout << comp1 << endl;
	cin >> comp1 >> comp2;
	cout << comp1 << comp2 << endl;

    return 0;

}

template<typename T>
void show(T a)// CComplex a
{
	//a.show();
	cout << a << endl; // T int  cout<<10<<endl;  CComplex
}

