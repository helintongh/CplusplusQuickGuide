/*** 
 * @Author: helintongh
 * @Date: 2020-09-20 13:13:30
 * @LastEditTime: 2020-09-20 13:19:35
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/STL库/有序集合与类结合.cpp
 */
#include <iostream>
#include <cstdlib>
// 使用无序关联容器包含的头文件
#include <unordered_set>
#include <unordered_map>

// 使用有序关联容器包含的头文件  红黑树
#include <set> // set multiset
#include <map> // map multimap
using namespace std;

class Student
{
public:
	Student(int id, string name)
		:_id(id), _name(name) {}
	bool operator<(const Student &stu)const // 定义比较运算符重载,才能使用set存储
	{
		return _id < stu._id; // 从小到大
	}
private:
	int _id;
	string _name;
	friend ostream& operator<<(ostream &out, const Student &stu);
};
ostream& operator<<(ostream &out, const Student &stu) // 输出运算符重载
{
	out << "id:" << stu._id << " name:" << stu._name << endl;
	return out;
}
int main()
{
    /*
        Student放入set里(放入红黑树中),
        那么如何进行排序呢? => 需要类里写排序方法,否则无法用set
    */
	set<Student> set1;  // multiset可以存储重复的元素

	set1.insert(Student(1020, "李广"));
	set1.insert(Student(1000, "张雯"));
	
	for (auto it = set1.begin();
		it != set1.end(); ++it)
	{
		cout << *it << endl;
	}

	return 0;
}