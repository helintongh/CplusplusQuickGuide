#include "pch.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
using namespace std;

/*
行为型模式：主要关注的是对象之间的通信
观察者模式Observer Pattern（发布-订阅模式）设计模式:主要关注的是对象的一对多的关系，也就是多个对象
都依赖一个对象，当该对象的状态发生改变时，其它对象都能够接收到相应的通知。

比如一下场景:
一组数据（数据对象）   =>  通过这一组数据 =>  生成曲线图(对象1)/柱状图(对象2)/圆饼图(对象3)
当数据对象改变时，对象1、对象2、对象3应该及时的收到相应的通知！

Observer1  Observer2   Observer3

		   Subject（主题）主题有更改，应该及时通知相应的观察者，去处理相应的事件
*/
// 观察者抽象类
class Observer 
{
public:
	// 处理消息的接口
	virtual void handle(int msgid) = 0;
};
// 第一个观察者实例
class Observer1 : public Observer
{
public:
	void handle(int msgid)
	{
		switch (msgid)
		{
		case 1:
			cout << "Observer1 recv 1 msg!" << endl;
			break;
		case 2:
			cout << "Observer1 recv 2 msg!" << endl;
			break;
		default:
			cout << "Observer1 recv unknow msg!" << endl;
			break;
		}
	}
};
// 第二个观察者实例
class Observer2 : public Observer
{
public:
	void handle(int msgid)
	{
		switch (msgid)
		{
		case 2:
			cout << "Observer2 recv 2 msg!" << endl;
			break;
		default:
			cout << "Observer2 recv unknow msg!" << endl;
			break;
		}
	}
};
// 第三个观察者实例
class Observer3 : public Observer
{
public:
	void handle(int msgid)
	{
		switch (msgid)
		{
		case 1:
			cout << "Observer3 recv 1 msg!" << endl;
			break;
		case 3:
			cout << "Observer3 recv 3 msg!" << endl;
			break;
		default:
			cout << "Observer3 recv unknow msg!" << endl;
			break;
		}
	}
};

// 主题类
class Subject
{
public:
	// 给主题增加观察者对象
	void addObserver(Observer* obser, int msgid)
	{
		_subMap[msgid].push_back(obser);
		/*auto it = _subMap.find(msgid);
		if (it != _subMap.end())
		{
			it->second.push_back(obser);
		}
		else
		{
			list<Observer*> lis;
			lis.push_back(obser);
			_subMap.insert({ msgid, lis });
		}*/
	}
	// 主题检测发生改变，通知相应的观察者对象处理事件
	void dispatch(int msgid)
	{
		auto it = _subMap.find(msgid);
		if (it != _subMap.end())
		{
			for (Observer *pObser : it->second)
			{
				pObser->handle(msgid);
			}
		}
	}
private:
	// msgid和对该msgid感兴趣的观察者list
	unordered_map<int, list<Observer*>> _subMap; // 多个观察者,所以用list
};

int main()
{
	Subject subject; // 定义一个主题
	Observer *p1 = new Observer1();
	Observer *p2 = new Observer2();
	Observer *p3 = new Observer3();
	// 增加主题类要通知的事件
	subject.addObserver(p1, 1);
	subject.addObserver(p1, 2);
	subject.addObserver(p2, 2);
	subject.addObserver(p3, 1);
	subject.addObserver(p3, 3);

	int msgid = 0;
	for (;;)
	{
		cout << "输入消息id:";
		cin >> msgid;
		if (msgid == -1)
			break;
		subject.dispatch(msgid);
	}

	return 0;
}