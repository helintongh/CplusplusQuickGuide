# decltype类型推导

## 1. 获取表达式的类型

`decltype`关键字用来在编译时推导出一个表达式的类型。语法如下

```c++
decltype(exp)
```

exp表示一个表达式，该关键字类似于sizeof，`decltype`的推导过程是在编译器完成的，并且不会真正计算表达式的值。

```c++
int x = 0;
decltype(x) y = 1;            // y -> int
decltype(x + y) z = 0;        // z -> int

const int &i = x;
decltype(i) j = y;            // j -> const int &

const decltype(z) *p = &z;    // *p -> const int, p -> const int *
decltype(z) *pi = &z;         // *pi -> int     , pi -> int *
decltype(pi) *pp = &pi;       // *pp -> int *   , pp -> int **
```

decltype的优点:

1. decltype得到的类型可以保留住表达式的引用以及const限定符。

## 2. decltype的推导规则

1. exp是标识符，类访问表达式，`decltype(exp)`和exp的类型一致
2. exp是函数调用，`decltype(exp)`和返回值的类型一致
3. 其他情况，若exp是一个左值，则`decltype(exp)`是exp类型的左值引用，否则和exp类型一致

第一种情况示例

```c++
class Foo
{
public:
  static const int Number = 0;
  int x;
};

int main()
{
  int n = 0;
  volatile const int &x = n;

  decltype(n) a = n;            // a -> int
  decltype(x) b = n;            // b -> volatile const int &

  decltype(Foo::Number) c = 0;  // c -> const int
  Foo foo;
  decltype(foo.x) d = 0;        // d -> int, 类访问表达式
}
```

第二种情况函数调用

```c++
int &func_int_r(void);            // 左值(理解为可寻址值或引用值即可)
int&& func_int_rr(void);          // x值(理解为右值引用，右值本身是xvalue将亡值,将亡值将要被移动的值)
int func_int(void);               // 纯右值(prvalue, 理解为返回的是一个常量)

const int& func_cint_r(void);     // 左值
const int&& func_cint_rr(void);   // x值
const int func_cint(void);        // 纯右值

const Foo func_cfoo(void);        // 纯右值

int x = 0;
decltype(func_int_r()) a1 = x;    // a1 -> int &
decltype(func_int_rr()) b1 = 0;   // b1 -> int &&
decltype(func_int()) c1 = 0;      // c1 -> int

decltype(func_cint_r()) a2 = x;   // a2 -> const int &
decltype(func_cint_rr()) b2 = 0;  // b2 -> const int &&
decltype(func_cint()) c2 = 0;     // c2 -> int

decltype(func_cfoo()) ff = Foo(); // ff -> const Foo
```

decltype的结果和函数的返回值类型保持一致

第三种带括号的表达式和加法运算表达式

```c++
struct Foo {int x; };
const Foo foo = Foo();

decltype(foo.x) a = 0;    // a -> int
decltype((foo.x)) b = a;  // b -> const int &

int n = 0, m = 0;
decltype(n + m) c = 0;    // c -> int
decltype(n += m) d = c;   // d -> int &
```

## 3. decltype的实际应用

decltype的应用一般是在泛型编程中。

```c++
#include <vector>

template <class ContainerT>
class Foo
{
  typename ContainerT::iterator it_; // 这里的类型定义可能有问题
public:
  void func(ContainerT& container)
  {
    it_ = container.begin();
  }
};

int main()
{
  typedef const std::vector<int> container_t;
  container_t arr;

  Foo<container_t> foo;
  foo.func(arr);

  return 0;
}
```

上面代码编译是没法通过的，因为container_t是const容器类型，而声明的`ContainerT::iterator`并不能包括所有的迭代器类型，当`ContainerT`是一个const类型时应该使用`const_iterator`。

如果是C++98/03只能想办法特化一个版本。

```c++
#include <vector>

template <class ContainerT>
class Foo
{
  typename ContainerT::iterator it_; // 这里的类型定义可能有问题
public:
  void func(ContainerT& container)
  {
    it_ = container.begin();
  }
};
// 特例化版本
template <class ContainerT>
class Foo<const ContainerT>
{
  typename ContainerT::const_iterator it_; // 这里的类型定义可能有问题
public:
  void func(const ContainerT& container)
  {
    it_ = container.begin();
  }
};

int main()
{
  typedef const std::vector<int> container_t;
  container_t arr;

  Foo<container_t> foo;
  foo.func(arr);

  return 0;
}
```

而如今直接通过`decltype`即可

```c++
#include <vector>

template <class ContainerT>
class Foo
{
  decltype(ContainerT().begin()) it_;
public:
  void func(ContainerT& container)
  {
    it_ = container.begin();
  }
};

int main()
{
  typedef const std::vector<int> container_t;
  container_t arr;

  Foo<container_t> foo;
  foo.func(arr);

  return 0;
}
```

这里引申出来`decltype`的另一个用途通过变量表达式抽取变量类型：

```c++
vector<int> v;
decltype<v>::value_type i = 0;
```

当只需要关心变量本身并不需要关心具体类型时就可以如上所示抽取。

标准库中的很多类型都是`decltype`来定义的，实际上这种定义方法对理解一些变量类型复杂但操作统一的代码片段大有好处。

```c++
typedef decltype(nullptr) nullptr_t; // 通过编译器关键字nullptr定义类型nullptr_t
typedef decltype(sizeof(0)) size_t;
```

这种定义方法的好处是，从类型的定义过程上就可以看出来这个类型的含义。

## 4.返回类型后置语法(auto和decltype结合使用)

decltype实际运用场景就是大大简化泛型编程的逻辑。

在泛型编程中，可能需要通过参数的运算来得到返回值的类型。

```c++
template <typename R, typename T, typename U>
R add(T t, U u)
{
  return t + u;
}

int a = 1;
float b = 2.0;
auto c = add<decltype(a + b)>(a, b);
```

上面这样就是`decltype`的一种使用方式，但是这种方法仍然很不方便，因为只有`add`函数才知道返回值应当如何推导。那么，在add函数的定义中获取到返回值类型可以吗？

先看一个错误写法:

```c++
template <typename T, typename U>
decltype(t + u) add(T t, U u) // error: t,u 尚未定义
{
  return t + u;
}
```

上面的语法无法编译，因为t和u在函数参数列表中，而C++的返回值是前置语法，在返回值定义的时候参数变量还不存在。

```c++
template <typename T, typename U>
decltype(T() + U()) add(T t, U u)
{
  return t + u;
}
```

再考虑到T和U可能是无参构造函数的类，还需要改进为如下:

```c++
template <typename T, typename U>
decltype((*(T*)0) + (*(U*)0)) add (T t, U u)
{
  return t + u;
}
```

上面的代码非常晦涩。

因此C++后面增加了返回值后置(trailing-return-type)语法，将decltype和auto结合起来完成返回值类型的推导。

```c++
template <typename T, typename U>
auto add(T t, U u) -> decltype(t + u)
{
  return t + u;
}
```

再看另一个例子

```c++
int &foo(int &i);
float foo(float& f);

template <typename T>
auto func(T& val) -> decltype(foo(val))
{
  return foo(val);
}
```

这个例子使用`decltype`结合返回值后置语法很容易推导出了`foo(val)`可能出现的返回值类型，并将其作用到了`func`上。

返回值类型后置语法，为了解决函数返回值类型依赖于参数而导致难以确定返回值类型的问题。