# 模板元编程(编译期计算)

## 模板基础总结

最新的 C++ 将模板分成了 4 类：**类模板 (class template)，函数模板 (function template)，别名模板 (alias template) 和 变量模板 (variable template)**。

前两者能产生新的类型，属于 **类型构造器 (type constructor)**；而后两者是 C++ 为前两者补充的简化记法，属于 **语法糖 (syntactic sugar)**。

类模板 和 函数模板 分别用于定义具有相似功能的 类 和 函数 (function)，是泛型中对 类型 和 算法 的抽象。在标准库中，容器 (container) 和 函数 都是 类模板 和 函数模板 的应用。

别名模板 和 变量模板 分别在 C++ 11 和 C++ 14 引入，分别提供了具有模板特性的 类型别名 (type alias) 和 常量 (constant) 的简记方法。前者 类模板的嵌套类 等方法实现，后者则可以通过 constexpr 函数、类模板的静态成员、函数模板的返回值 等方法实现。例如，C++ 14 中的 别名模板 `std::enable_if_t<T>` 等价于 `typename std::enable_if<T>::type`，C++ 17 中的 变量模板 `std::is_same<T, U>` 等价于 `std::is_same<T, U>::value`。尽管这两类模板不是必须的，但一方面可以增加程序的可读性，另一方面可以提高模板的编译性能。

C++ 中的 模板参数 (template parameter/argument) 可以分为三种：**值参数**，**类型参数**，**模板参数**.

C++ 的模板机制仅仅提供了 纯函数 (pure functional) 的方法，即不支持变量，且所有的推导必须在编译时完成。但是 C++ 中提供的模板是 图灵完备 (turing complete) 的，所以可以使用模板实现完整的元编程。

元编程的基本 演算规则 (calculus rule) 有两种：**编译时测试** (compile-time test) 和 **编译时迭代** (compile-time iteration)，分别实现了 控制结构 (control structure) 中的 **选择** (selection) 和 **迭代** (iteration)。基于这两种基本的演算方法，可以完成更复杂的演算。

另外，元编程中还常用模板参数传递不同的 策略 (policy)，从而实现 依赖注入 (dependency injection) / 控制反转 (Inversion of Control)。例如，`std::vector<typename T, typename Allocator = std::allocator<T>>` 允许传递 Allocator 实现自定义内存分配。

## 编译时测试

编译时测试相当于面向过程编程中的选择语句,可以实现`if else`/`switch`的选择逻辑。

在 C++ 17 之前，编译时测试是通过模板的实例化和特化实现的 —— 每次找到最特殊的模板进行匹配；而 C++ 17 提出了使用 `constexpr-if` 的编译时测试方法。

### 模板实例化和特化实现编译时测试

直接看代码:

```c++
#include <cstdio>

template <int n>
struct factorial {
    static const int value =
        n * factorial<n - 1>::value;
};
template <>
struct factorial<0> {
    static const int value = 1;
};

int main()
{
    printf("%d\n", factorial<10>::value);
}
```

上面定义了一个递归的阶乘函数,可以看到通过两个特例化值实现了编译时递归(分支)

模板元编程报错信息复杂所以还需注意差错处理,上面的程序可以改成:

```c++
template <int n>
struct factorial {
    static_assert(
        n >= 0,
        "Arg must be non-negative");
    static const int value =
        n * factorial<n - 1>::value;
};
```

通过`static_assert`断言确保参数永远不会是负数。

要进行编译时测试最重要是的需要把计算转为类型推导。

上面代码的汇编为:

```x86asm
.LC0:
        .string "%d\n"
main:
        push    rbp
        mov     rbp, rsp
        mov     esi, 3628800
        mov     edi, OFFSET FLAT:.LC0
        mov     eax, 0
        call    printf
        mov     eax, 0
        pop     rbp
        ret
```

可以看到直接出现了常量3628800

### 测试表达式

类似于静态断言，编译时测试的对象是**常量表达式(constexpr)**，即编译时能得出结论的表达式。

以不同的常量表达式作为参数，可以构造各种需要的模板重载。例如下面的代码演示如何构造一个编译时函数`isZero<Val>`，编译时判断`Val`是不是0。

```cpp
template <unsigned Val> struct _isZero {
    constexpr static bool value = false;
};

template <> struct _isZero <0> {
    constexpr static bool value = true;
};

template <unsigned Val>
constexpr bool isZero = _isZero<Val>::value;

int main
{
    static_assert (!isZero<1>, "compile error");
    static_assert (isZero<0>, "compile error");
}
```