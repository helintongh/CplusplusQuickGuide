/*
C 调用 C++:无法直接调用了！怎么办？ 把C++源码扩在extern "C"
C++ 调用 C代码:无法直接调用了！怎么办？ 把C函数的声明扩在extern "C"里面

*/


extern "C"
{
	// sum  "UND"
	int sum(int a, int b) // sum_int_int .text
	{
		return a + b;
	} 
	//C++在.cpp文件中实现了sum函数C语言无法调用。可以按照C的规则生成sum函数。如上
}

//无法解析的外部符号 
//"int __cdecl sum(int,int)" (?sum@@YAHHH@Z)，该符号在函数 _main 中被引用
extern "C"
{
	int sum(int a, int b);  // sum  "UND"
	//在.c文件中实现了sum函数C++无法调用。可以按照C的规则生成sum函数。如上
}

// __FILE__
// __LINE__
// 只要是c++编译器,都内置了__cplusplus宏名
/*
下面这段代码的作用是符号生成按C符号生成(无论是c++还是c编译器)
*/
#ifdef __cplusplus
extern "C"
#endif
{
	int sum(int a, int b) // sum_int_int .text
	{
		return a + b;
	}
#ifdef __cplusplus 
}
#endif
