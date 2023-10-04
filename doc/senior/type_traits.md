# 类型萃取

模板元编程还有一个重要的前置知识，就是类型萃取其头文件为`type_traits`，比如模板编程中一个特殊概念**替换失败非错(SFINAE)**全称为:substituion failure is not an error。它的实现就依赖于类型萃取

## 类型萃取是什么

类型萃取就是实现在编译器计算，查询，判断，转换和选择的接口，增强了泛型编程的能力，增加了程序的弹性，使得在编译器就能做到优化改进甚至于排错。

## 类型萃取的分类

### 1. 基本的类型traits

```c++
template <typename Type>
struct GetLeftSize
{
  static const int value = 1;
};

// 类型萃取方式定义编译器常量
template <typename Type>
struct GetLeftSize : std::integral_constant<int , 1>
{
};
```

上面两个结构体都可以通过`GetLeftSize:value`来获取常量1。

大部分情况下这种api没用(个人观点)，甚至于我觉得第一种写法更方便。

下面看一个重要的编译期常量包装为一个类型的type_trait ---- `integral_constant`,它实现大致如下：

```c++
template <class T, T v>
struct integral_constant
{
  static const T value = v;
  typedef T value_type;
  typedef integral_constant<T, v> type;
  operator value_type() { return value; }
}
```

其有一个成员变量value，可以通过`integral_constant::value`来获取其所代表的真正值。常见的用法是从`integral_constant`派生，从而可以通过继承得到value。

而true_type和false_type就是`integral_constant`的一个实例:

```c++
typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;
```

基本的类型萃取唯一有用的，我认为是`std::true_type`和`std::false_type`。这两个定义了编译期的true和false类型。其余很难遇到。

### 2. 类型判断的traits

实现反射需要这种萃取。这些type_traits都是从`std::integral_constant`派生的，用来检测模板类型是否为某种类型

直接查阅网站即可。只举几个重要的类型判断

```c++
/*
is_void;           // T是否void类型
is_pointer;        // T是否是指针类型(包括函数指针,但不包括成员函数指针)
is_class;          // T是否是类类型
is_function;       // T是否是函数类型
is_polymorphic;    // T是否有虚函数
is_abstract;       // T是否是抽象类
is_const;          // T是否为const修饰
*/

#include <iostream>
#include <type_traits>

class Foo()
{
private:
  int x;
};

int main()
{
  std::cout << "is_const:" << std::endl;
  std::cout << "int: " << std::is_const<int>::value << std::endl;
  std::cout << "class: " << std::is_class<Foo>::value << std::endl;
  return 0;
}
```

上面代码输出:

```
is_const:
int: 0
class: 1
```

判断类型的萃取一般和`std::enable_if`结合使用,通过SFINAE特性实现更强大的重载。 [下一章](./sfinae.md)会着重介绍该技术。

### 3. 判断两个类型之间关系的traits

```c++
template <class T, class U>
struct is_same;                         // 判断两个类型是否相同

template <class Base, class Derived>
struct is_base_of;                      // 判断Base类型是否为Derived类型的基类

template <class From, class To>
struct is_convertible;                  // 判断前面的模板参数类型能否转换为后面的模板参数类型
```

```c++
#include <iostream>
#include <type_traits>

class A{};

class B : public A {};

class C {};

int main()
{
  std::cout << std::is_same<int, int>::value << "\n"; // 1

  std::cout << std::is_base_of<A, B>::value << "\n";  // 1
  std::cout << std::is_base_of<B, A>::value << "\n";  // 0
  std::cout << std::is_base_of<C, B>::value << "\n";  // 0

  bool b2a = std::is_convertible<B*, A*>::value;      // 1
  bool a2b = std::is_convertible<A*, B*>::value;      // 0
  bool b2c = std::is_convertible<B*, C*>::value;      // 0

  std::cout << b2a << "\n";
  std::cout << a2b << "\n";
  std::cout << b2c << "\n";
}
```

上面代码的输出为:
```
1
1
0
0
1
0
0
```


下面解释下代码和其输出的要点：
`is_base_of`将第一个模板参数作为基类类型，使用时需要将基类类型作为第一个模板参数。
`std::is_convertible<B*, A*>::value`，由于`A*`是B的基类指针，可以隐式转换的所以结果为true也就是1。


### 4. 类型转换的traits

这个查阅相关网站即可。我很少用到。

常用的也就`remove_reference`去除引用。而且c++提供了`std::decay`语法糖一个函数去除引用和cv符号。

看一个例子吧，根据模板参数类创建对象时，要移除引用,代码如下：

```c++
template <typename T>
typename std::remove_reference<T>::type *Create()
{
  typedef typename std::remove_reference<T>::type U;
  return new U();
}
```

### **5.根据条件选择的traits**

`std::conditional`在编译期根据判断式选择两个类型中的一个，和条件表达式语义类似，原型如下:


```c++
template<bool B, class T, class F>
struct conditional;
```

```c++
#include <iostream>
#include <type_traits>
#include <typeinfo>
#include <cxxabi.h>

int main()
{
  typedef std::conditional<(sizeof(long long) > sizeof(long double)) , long long, long double>::type max_size_t;

  std::cout << typeid(max_size_t).name() << " => " << abi::__cxa_demangle(typeid(max_size_t).name(), NULL, NULL, NULL) << std::endl;
  return 0;
}
```

上面代码输出为`e => long double`。由此可见其用法，如果B为true则,`conditional::type`为T，否则为F。

### 6. 获取可调用对象返回类型的traits

核心是`std::result_of`

### 7. 根据条件禁用或启用某种或某些类型traits

这在 [后一章节SFINAE](./sfinae.md)详谈。对于模板编程非常重要。

# 总结

类型萃取分为以下7种，用的时候再去查api即可

1. 基本的type_traits，基本不会用到，但是是标准库实现其他几种类型的基础
2. 类型判断的traits
3. 判断两个类型之间关系的traits
4. 类型转换的traits
5. 根据条件选择的traits
6. 获取可调用对象返回类型的traits
7. 根据条件禁用或启用某种或某些类型的traits

其中重点是5.**根据条件选择的traits**以及7.**根据条件禁用或启用某种或某些类型的traits**。

如果需要实现反射的话那么2也比较重要。