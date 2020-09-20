/*** 
 * @Author: helintongh
 * @Date: 2020-09-20 13:20:14
 * @LastEditTime: 2020-09-20 13:30:52
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/STL库/有序关联容器之映射表.cpp
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
	Student(int id=0, string name="")
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
    map<int, Student> stuMap;
    stuMap.insert({ 1000, Student(1000, "张伟") });
    stuMap.insert({ 1020, Student(1020, "曾小贤") });
    stuMap.insert({ 1030, Student(1030, "关谷") });

    // 删除
    // stuMap.erase(it) stuMap.erase(1020) => 删除了曾小贤这条数据
    /*
         []运算符有副作用当map中没有1020项时会插入该数据
            所以类的构造函数中成员变量要给默认值
        举例:假设map中没有2000 => stuMap[2000] => [2000, V()]
    */

    // cout << stuMap[1020] << endl;   stuMap.find(key)
	auto it = stuMap.begin();
	for (; it != stuMap.end(); ++it)
	{
		cout << "key:" << it->first << " value:" << it->second << endl;
	}
	cout << endl;

	return 0;
}