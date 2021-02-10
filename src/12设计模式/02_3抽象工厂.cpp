#include <iostream>
#include <string>
#include <memory>
using namespace std;
/*
简单工厂 Simple Factory : 
把对象的创建封装在一个接口函数里面，通过传入不同的标识，返回创建的对象
客户不用自己负责new对象，不用了解对象创建的详细过程

提供创建对象实例的接口函数不闭合，不能对修改关闭

工厂方法 Factory Method
Factory基类，提供了一个纯虚函数（创建产品），定义派生类（具体产品的工厂）负责创建对应的
产品，可以做到不同的产品，在不同的工厂里面创建，能够对现有工厂，以及产品的修改关闭

实际上，很多产品是有关联关系的，属于一个产品簇，不应该放在不同的工厂里面去创建，这样
一是不符合实际的产品对象创建逻辑，二是工厂类太多了，不好维护

抽象工厂 Abstract Factory
把有关联关系的，属于一个产品簇的所有产品创建的接口函数，放在一个抽象工厂里面AbstractFactory
，派生类（具体产品的工厂）应该负责创建该产品簇里面所有的产品

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
// 系列产品2
class Light
{
public:
	virtual void show() = 0;
};
class BmwLight : public Light
{
public:
	void show() { cout << "BMW light!" << endl; }
};
class AudiLight : public Light
{
public:
	void show() { cout << "Audi light!" << endl; }
};

// 工厂方法 => 抽象工厂(对有一组关联关系的产品簇提供产品对象的统一创建)
class AbstractFactory
{
public:
	virtual Car* createCar(string name) = 0; // 工厂方法 创建汽车
	virtual Light* createCarLight() = 0; // 工厂方法 创建汽车关联的产品，车灯
};
// 宝马工厂
class BMWFactory : public AbstractFactory
{
public:
	Car* createCar(string name)
	{
		return new Bmw(name);
	}
	Light* createCarLight()
	{
		return new BmwLight();
	}
};
// 奥迪工厂
class AudiFactory : public AbstractFactory
{
public:
	Car* createCar(string name)
	{
		return new Audi(name);
	}
	Light* createCarLight()
	{
		return new AudiLight();
	}
};
int main()
{
	unique_ptr<AbstractFactory> bmwfty(new BMWFactory());
	unique_ptr<AbstractFactory> audifty(new AudiFactory());
	unique_ptr<Car> p1(bmwfty->createCar("X6"));
	unique_ptr<Car> p2(audifty->createCar("A8"));
	unique_ptr<Light> l1(bmwfty->createCarLight());
	unique_ptr<Light> l2(audifty->createCarLight());

	p1->show();
	l1->show();

	p2->show();
	l2->show();

	return 0;

	return 0;
}