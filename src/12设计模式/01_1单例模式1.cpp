#include <iostream>
#include <mutex>
using namespace std;

/*
单例模式：一个类不管创建多少次对象,永远只能得到该类型一个对象的实例
A *p1 = new A();
A *p2 = new A();
A *p3 = new A(); 

常用到的,比如日志模块,数据库模块

单例模式：
饿汉式单例模式：还没有获取实例对象,实例对象就已经产生了
懒汉式单例模式：唯一的实例对象,直到第一次获取它的时候,才产生
*/
// 饿汉式单例模式 一定是线程安全的 => 先创建导致程序会变慢
class Singleton
{
public:
	static Singleton* getInstance() // #3 获取类的唯一实例对象的接口方法
	{
		return &instance;
	}
private:
	static Singleton instance; // #2 定义一个唯一的类的实例对象 => 提供给用户的,只有一个 => static 是在.data段先于函数创建
	Singleton() // #1 构造函数私有化 <= 控制生成的个数,就要限制构造函数
	{

	}
	Singleton(const Singleton&) = delete;			// 对象的默认拷贝构造和赋值构造全部要删除
	Singleton& operator=(const Singleton&) = delete;
};
Singleton Singleton::instance; // 静态变量要在类外初始化

int main()
{
	Singleton *p1 = Singleton::getInstance();
	Singleton *p2 = Singleton::getInstance();
	Singleton *p3 = Singleton::getInstance();

	// 这三个指针的地址全是一样的
	//Singleton t = *p1;  => 增加了两条delete后不能做这一个操作
	return 0;
}