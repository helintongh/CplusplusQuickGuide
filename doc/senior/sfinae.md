# SFINAE:替换失败非错


替换失败非错（substituion failure is not an error），英文简称为 SFINAE。

编译器在匹配重载函数时会匹配所有的重载函数，找到一个最精确匹配的函数，在匹配过程中可能会存在一些失败，当匹配失败时或者找到多个匹配程度相当的函数时则编译器会报错。

而SFINAE则是匹配失败时会尝试匹配其他的重载函数。

比如如下例子:

```c++
template <typename T>
void Fun(T*) {}

template <typename T>
void Fun(T) {}
int main()
{
  Fun(1);

  return 0;
}
```

上面的代码将会匹配第二个重载函数，在匹配过程中，当匹配到`void Fun(T*)`时，将一个非0的整数来替换`T*`是错误的，此时编译器不会报错而是继续匹配其他的重载函数，如果最后发现`void Fun(T)`能匹配上，整个过程就不会报错。这个规则就是SFINAE(替换失败并非错误)

## 根据条件禁用或启用某种或某些类型的traits

C++ 11新增加了根据条件禁用或启用某种或某些类型的traits，其关键字为`std::enable_if`。其利用SFINAE实现根据条件选择重载函数。

函数原型如下：

```c++
template<bool B, class T = void>
struct enable_if;
```

## enable_if基本使用

`std::enable_if`仅在函数在判断条件B为true时有效。其基本用法如下:

```c++
#include <type_traits>
#include <typeinfo>
#include <cxxabi.h>

template <class T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type foo(T t)
{
  return t;
}

int main()
{
  auto r = foo(1);          // 返回整数1
  auto r1 = foo(1.2);       // 返回浮点数1.2
  // auto r2 = foo("test"); // 编译错误
}
```

上面的代码对模板参数做了限制，只能是arithmetic(整型和浮点型)，如果非arithmetic编译不通过。因为`std::enable_if`只对满足判断式条件的函数有效，对其他函数无效。

上面的例子enable_if作用于返回值。同时其还可以用于模板定义，类模板和特化以及入参类型的限定

```c++
#include <type_traits>

// 对入参类型做了限制，即第二个入参为integral类型
template <class T>
T foo2(T t, typename std::enable_if<std::is_integral<T>::value, int>::type = 0)
{
  return t;
}

// 对模板参数T做了限制,T只能是integral类型
template <class T,
  class = typename  std::enable_if<std::is_integral<T>::value, int>::type>
T foo3(T t)
{
  return t;
}

template<class T, class Enable = void>
class A;

// 模板特例化时，对模板参数做限定，模板参数类型只能为浮点型
template<class T>
class A<T, typename std::enable_if<std::is_floating_point<T>::value>::type> {};

int main()
{
  foo2(1, 2);       // 满足限定条件
  // foo2(1, "");   // 编译报错，第二个参数应该为integral类型

  foo3(1);          // ok
  // foo3(1.2);     // 编译报错，模板参数应该为integral类型

  A<double> a;      // ok
  // A<int> a;      // 编译报错，不满足偏特化的限定条件，模板参数应该为integral类型
}
```

## enable_if适用所有情况的用法

`std::enable_if`可以通过判断式和非判断式来将入参分为两大类，从而满足所有入参的类型。代码如下


```c++
#include <type_traits>
#include <iostream>

template <class T>
typename std::enable_if<std::is_arithmetic<T>::value, int>::type foo1(T t)
{
  std::cout << "is arithmetic, value is: ";
  std::cout << t << std::endl;
  return 0;
}

template <class T>
typename std::enable_if<!std::is_arithmetic<T>::value, int>::type foo1(T t)
{
  std::cout << "not arithmetic, value is: ";
  std::cout << t << std::endl;
  return 1;
}

int main()
{
  foo1("test");

  foo1(1);
  foo1(2.0);
}
```

上述代码输出如下：
```
not arithmetic, value is: test
is arithmetic, value is: 1
is arithmetic, value is: 2
```

上面代码对`arithmetic`类型的入参返回0，对于非arithmetic的类型则返回1，通过arithmetic将所有的入参类型分为了两大类进行处理。

`std::enable_if`的第二个模板参数的默认模板参数是`void`类型，因此当函数无需返回值时，后面的模板参数可以省略。

```c++
#include <type_traits>
#include <typeinfo>
#include <cxxabi.h>
#include <string>

#include <iostream>

template <class T>
typename std::enable_if<std::is_arithmetic<T>::value>::type foo1(T t)
{
  std::cout << abi::__cxa_demangle(typeid(T).name(), NULL, NULL, NULL) << std::endl;
}

template <class T>
typename std::enable_if<std::is_same<T, std::string>::value>::type foo1(T &t)
{
  std::cout << abi::__cxa_demangle(typeid(T).name(), NULL, NULL, NULL) << std::endl;
}

int main()
{
  foo1(2.90);
  std::string test = "test string";
  foo1(test);
}
```

上述代码输出
```
double
std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >
```

上面的代码展示了`std::enable_if`具备限制模板参数的作用。可以用其在编译器检查输入模板参数是否有效。比如，在上例中限定了`foo1`函数的入参必须为整型或浮点型以及string。如果不为上述类型会在编译时报错，从而避免了直到运行时才能发现错误。

`std::enable_if`作用: 可以实现强大的重载机制，一般函数返回值不同而参数相同不允许重载，而使用`std::enable_if`仅仅返回值不同就能进行重载操作。

由此可知可以使用`std::enable_if`来消除复杂度较高的`switch-case/if-else`语句，有效提高代码可维护性和降低复杂度。

下面看一个例子,实现把数字转为string的函数:

```c++
template <typename T>
std::string ToString(T t)
{
  if (typeid(T) == typeid(int) || typeid(T) == typeid(double) || typeid(T) == typeid(float))
  {
    std::stringstream ss;
    ss << t;
    return ss.str();
  }
}
```

上面的代码可以修改为如下:

```c++
template <class T>
typename std::enable_if<std::is_arithmetic<T>::value, std::string>::type
    ToString(T& t) { return std::to_string(t); }

template <class T>
typename std::enable_if<std::is_same<T, std::string>::value, std::string>::type
    ToString(T& t) { return t; }
```

完整代码:

```c++
#include <string>
#include <iostream>
#include <typeinfo>

template <class T>
typename std::enable_if<std::is_arithmetic<T>::value, std::string>::type
    ToString(T& t) { return std::to_string(t); }

template <class T>
typename std::enable_if<std::is_same<T, std::string>::value, std::string>::type
    ToString(T& t) { return t; }

int main()
{
  int a = 30;
  std::string str = ToString(a);
  std::cout << str << std::endl;

  std::string str2 = ToString(str);
  std::cout << str2 << std::endl;
  return 0;
}
```

代码输出为:

```
30
30
```

代码逻辑是对于arithmetic类型调用`std::to_string(t)`,对于string类型则返回其本身。

上述代码修改为如下就是更加符合现代C++风格的函数了。

```c++
template <class T>
typename std::enable_if<std::is_arithmetic<T>::value, std::string>::type
    ToString(T&& t) { return std::to_string(t); }

std::string str = ToString(std::move(30));
```

## 总结

SFINAE核心函数是`std::enable_if`其对于优化旧有逻辑，减少代码复杂度非常有帮助。