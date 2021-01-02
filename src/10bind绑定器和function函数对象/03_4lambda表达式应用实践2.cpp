#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <map>
#include <memory>
#include <queue>
using namespace std;
/*
既然lambda表达式只能使用在语句当中，如果想跨语句使用之前定义好的lambda表达式，
怎么办？用什么类型来表示lambda表达式？
当然是用function类型来表示函数对象的类型了   bind1st/bind2nd bind绑定器

lambda表达式 => 函数对象   
*/
class Data
{
public:
	Data(int val1 = 10, int val2 = 10) :ma(val1), mb(val2) {}
	//bool operator>(const Data &data)const { return ma > data.ma; } 
	//bool operator<(const Data &data)const { return ma < data.ma; }
	int ma;
	int mb;
};
int main()
{
	// 优先级队列 => 如何划分优先级?Data没办法进行比较的,Data类中指定<和>不方便
	//priority_queue<Data> queue;
	using FUNC = function<bool(Data&, Data&)>; // 相当于重命名function<bool(Data&, Data&)>为FUNC
	priority_queue<Data, vector<Data>, FUNC> maxHeap
	(
		[](Data &d1, Data &d2)->bool
		{
			return d1.mb > d2.mb; // 通过mb成员变量从大到小排序
		}
	);
	maxHeap.push(Data(10, 20));
	maxHeap.push(Data(15, 15));
	maxHeap.push(Data(20, 10));
}