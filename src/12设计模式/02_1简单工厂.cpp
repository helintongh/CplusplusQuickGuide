#include <iostream>
#include <string>
#include <memory>
using namespace std;
/*
简单工厂 Simple Factory : 

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

// 简单工厂
enum CarType
{
	BMW,AUDI
};
class SimpleFactory
{
public:
	Car* createCar(CarType ct) // 软件设计 “开-闭”,设计上不太好会不断更新代码
	{
		switch (ct) // 根据传入参数直接返回构造的对象
		{
		case BMW:
			return new Bmw("X1");
		case AUDI:
			return new Audi("A6");
		default:
			cerr << "传入工厂的参数不正确:" << ct << endl;
			break;
		}
		return nullptr;
	}
};
int main()
{
	// 上述不好的地方,开发者必须牢记派生类的名字
	// Car *p1 = new BMW("X1");
	// Car *p2 = new Audi("A6");

	/*
	简单工厂模式就可以通过类直接创建X1和A6
	SimpleFactory *factory = new SimpleFactory();
	Car *p1 = factory->createCar(BMW);
	Car *p2 = factory->createCar(AUDI);
	*/

	unique_ptr<SimpleFactory> factory(new SimpleFactory());
	unique_ptr<Car> p1(factory->createCar(BMW));
	unique_ptr<Car> p2(factory->createCar(AUDI));
	p1->show();
	p2->show();

	return 0;
}