/*** 
 * @Author: helintongh
 * @Date: 2020-09-06 16:07:34
 * @LastEditTime: 2020-09-06 16:40:18
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/多重继承/普通继承示例.cpp
 */
#include <iostream>
using namespace std;


class A
{
public:
private:
	int ma;
};
class B : public A
{
public:
private:
	int mb;
};
/*
A a; 4个字节
B b; ma,mb  8个字节=8个字节 
*/

