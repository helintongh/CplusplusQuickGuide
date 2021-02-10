#include <iostream>
#include <string>
#include <memory>
using namespace std;
/*
工厂方法 Factory Method

工厂模式：主要是封装了对象的创建
*/

// 系列产品1
class Car
{
public:
	Car(string name) :_name(name) {}
	virtual void show() = 0;
private:
	string _name;
};

class Bmw : public Car
{
public:
	Bmw(string name) :Car(name) {}
	void show()
	{
		cout << "获取了一辆宝马汽车:" << _name<<endl;
	}
};
class Audi : public Car
{
public:
	Audi(string name) :Car(name) {}
	void show()
	{
		cout << "获取了一辆奥迪汽车:" << _name<<endl;
	}
};
// 工厂方法
class Factory
{
public:
	virtual Car* createCar(string name) = 0;
}
// 宝马工厂
class BMWFacoty : public Factory
{
public:
	Car* createCar(string name)
	{
		return new Bmw(name);
	}
};
// 奥迪工厂
class AudiFactory : public Factory
{
public:
	Car* createCar(string name)
	{
		return new Audi(name);
	}
};
int main()
{
	// 现在考虑产品  一类产品（有关联关系的系列产品）
	/*
	工厂模式缺陷:
	比如华为有手机也有手机耳机，不可能创建一个手机工厂
		再建一个手机耳机工厂这会造成工厂类非常多。
			往往是相关联产品放在一个工厂里
	=> 抽象工厂模式
	*/
	unique_ptr<Factory> bmwfty(new BMWFacoty());
	unique_ptr<Factory> audifty(new AudiFactory());
	unique_ptr<Car> p1(bmwfty->createCar("X6"));
	unique_ptr<Car> p2(bmwfty->createCar("A8"));
	p1->show();
	p2->show();

	return 0;
}