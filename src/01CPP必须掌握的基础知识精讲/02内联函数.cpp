

/*
==>inline内联函数 和 普通函数的区别?? -- 内联少了函数调用开销 内联成功不会在符号表生成符号
inline内联函数:在编译过程中,就没有函数的调用开销了,在函数的调用点
直接把函数的代码进行展开处理了

inline 函数不再生成相应的函数符号

inline只是建议编译器把这个函数处理成内联函数
但是不是所有的inline都会被编译器处理成内联函数 -- 比如递归,复杂逻辑的函数

debug版本上,inline是不起作用的； inline只有再release版本下才能出现
linux执行这两个指令可以看出内联与普通的区别:
g++ -c main.cpp -O2 
objdump -t main.o
*/

inline int sum(int x, int y) // *.o sum_int_int .text 内联函数不生成该指令
{
	return x + y;
}

int main()
{
	int a = 10;
	int b = 20;

	int ret = sum(a, b); // 内联相当于这里直接a+b
	// 此处有标准的函数调用过程 参数压栈, 函数栈帧的开辟和回退
	// 有函数调用的开销
	// x+y  mov add mov 函数调用开销有可能远远大于函数指令本身
	// 此时使用内联函数

	return 0;
}