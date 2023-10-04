# auto类型推导

## 1. auto的基本使用

C++中`auto`和`decltype`关键字实现类型推导，这两个关键字用来获取复杂的类型，可以简化书写提高编码效率。而`decltype`更是大大简化了模板元编程。

`auto`基本用法

```c++
#include <iostream>

int main()
{
  auto x = 5;                 // x是int型
  auto pi = new auto(1);      // pi被推到为int*
  const auto *v = &x, u = 6;  // v是const int *, u是const int类型
  static auto y = 0.0;        // y是double

  // 下面是错误代码
  auto int r;                 // auto不能表示存储类型指示符
  auto s;                     // 无法推导出s的类型
}
```

注意:

1. 使用`auto`声明的变量比如马上初始化，否则编译器无法推导出其实际类型。只有推导出实际类型编译时才能将`auto`占位符替换为真正的类型。

## 2.auto的推导规则

auto可以与指针和引用结合使用，还可以带上cv限定符(const和volatile限定符的统称)

```c++
int x = 0;

auto *a = &x;       // a -> int*, auto被推导为int
auto b = &x;        // b -> int*, auto被推导为int*
auto &c = x;        // c -> int&, auto被推导为int
auto d = c;         // d -> int, auto被推导为int

const auto e = x;   // e -> const int
auto f = e;         // f -> int

const auto& g = x;  // g -> const int&
auto &h = g;        // f -> const int&
```

上面示例可以得出auto的两条规则:

1. 当不声明为指针或引用时,auto的推导结果和初始化表达式抛弃引用和cv限定符后类型一致。
2. 当声明为指针或引用时，auto的推导结果将保持初始化表达式的cv属性。

注意: auto不能用于函数参数。且auto的推导规则和函数模板参数的推导有相似处。

## 3.auto的限制

1. auto不能用于函数参数
2. auto不能用于非静态成员变量
3. auto无法定义数组
4. auto无法推导出模板参数

```c++
void func(auto a = 1) {} //error: auto不能用于函数参数
struct Foo
{
  auto var1_ = 0; // error: auto不能用于非静态成员变量
  static const auto var2_ = 0; // var2_ -> static const int
};

template <typename T>
struct Bar {};

int main()
{
  int arr[10] = {0};
  auto aa = arr;      // aa -> int*
  auto rr[10] = arr;  // error: auto无法定义数组

  Bar<int> bar;
  Bar<auto> bb = bar; // error: auto无法推导出模板参数
}
```

## 4.auto的实际使用场景

1. 替换迭代器iterator类型声明

```c++
#include <map>

int main()
{
  std::map<double, double> mp;
  // ...
  std::map<double, double>::iterator it = mp.begin();
  // 上面一行可以替换为如下
  auto it2 = mp.begin();
}
```

2. 当无法知道变量应该被定义成什么类型的时候

```c++
class Foo
{
public:
  static int get(void)
  {
    return 0;
  }
};

class Bar
{
public:
  static const char *get(void)
  {
    return "0";
  }
};

template <class A>
{
  auto val = A::get();
}

int main(void)
{
  func<Foo>();
  func<Bar>();
  return 0;
}
```