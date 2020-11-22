// 引用sum.cpp文件里定义的全局变量 以及函数
extern int gdata;  // gdata *UND*
int sum(int, int) ; // sum *UND*

int data = 20; // data .data

int main() // main .text
{
	int a = gdata;
	int b = data;

	int ret = sum(a,b);

	return 0;
}
