## C++20协程

首先要明确一点C++官方协程是无栈协程并且实现比较原始,所以现在协程主要是给写库的人使用的。

怎么用协程写一个实际运用,我推荐一个我重度参与的基于c++ 20协程的http client库 [cinatra](https://github.com/qicosmos/cinatra/blob/master/include/cinatra/coro_http_client.hpp) 可以作为参考。

C++的协程api总共有三大组件:

- Operators & Awaitable Type 操作与等待类型
- Promise 代表了一个异步操作的结果
- Coroutine Handle 协程处理

### 理解协程

要理解协程首先要理解普通程序的调用栈。

```cpp
int mul(int a, int b) {
    return a * b;
}

int main() {
    int c = mul(4, 5);
}
```

其中实现的`mul`函数对应的汇编如下图:

![](./resource/coro/01.png)

由图可以知道程序是:

一组有序的指令,而最关键的是汇编指令`imul`,前面的指令都是把字节从源位置传到目的位置。而`imul`指令是机器行为的抽象,并且实现了机器状态之间的转换。

为了解释更清楚一点,函数在整个程序的生命周期重总共有四种状态:

- Invocation(调用)
  
    跳转(转到jump to)到函数起始地址

- Activation(激活)

    跳进(jump into)函数的某个位置(可能是起始地址可能是函数别的地址)

- Suspension(暂停)

    在函数执行完成前跳转到另一个协程中。

- Finalization(完成)

    清理掉函数调用栈(函数执行完成)

普通的程序(后面统一叫例程,例程包含多线程或多进程程序)就只支持两种操作:: Invoke/Finalize

调用如下图:

![](./resource/coro/02.png)

普通的函数调用后直接到完成然后就结束了。

看上面的`mul`函数代码的汇编指令,其中Invake阶段就是汇编中`call`指令可以清楚看到调用的就是`mul`函数,然后当`mul`函数到了`ret`指令时其就已经执行完成(Finalize)了。

![](./resource/coro/03.png)


理解协程还需要懂得两个基本概念(简单来说):

**Process进程**: 在OS上运行程序的方式(一组有序的指令执行)

**thread线程**: 进程中的控制流的抽象(处理器抽象(CPU))

#### 协程支持的四种操作:

协程是一种特殊的子例程,尽管理论上来讲两者毫无关联,但是实际机器中协程是例程的超集。

协程中比较难理解的只有yield概念,看如下python代码计算斐波那契数列:

```py
#!/usr/bin/python
# -*- coding: UTF-8 -*-

def fab(max):
    n, a, b = 0, 0, 1
    while n < max:
        yield b      # 使用 yield
        a, b = b, a + b
        n = n + 1

for n in fab(5):
    print(n)

```

这里yield的作用就是把一个函数变成一个generator,带有yield 的函数不再是一个普通函数,Python解释器会将其视为一个generator.调用`fab(5)`不会执行fab函数,而是返回一个`iterable`对象.在`for`循环执行时,每次循环都会执行`fab`函数内部的代码,执行到`yield b`时,`fab`函数就返回一个迭代值,下次迭代时,代码从`yield b`的下一条语句继续执行,而函数的本地变量看起来和上次中断执行前是完全一样的,于是函数继续执行,直到再次遇到`yield`。

协程可以通过yield(“让步”)来调用其它协程,接下来的每次协程被调用时,从协程上次yield返回的位置接着执行,通过yield方式转移执行权的协程之间不是调用者与被调用者的关系,而是彼此对称、平等的。由于协程不如子例程那样被普遍所知,下面对它们作简要比较： 




| 操作     | 例程        | 协程      | 说明                       |
| -------- | ----------- | --------- | -------------------------- |
| Invoke   | supported   | supported | 转到程序(函数)的开始(call) |
| Finalize | supported   | supported | 清理堆栈并返回             |
| Suspend  | unsupported | supported | yield当前控制流程(函数)    |
| Resume   | unsupported | supported | 在程序暂停点恢复           |

下面就是这四种操作

![](./resource/coro/04.png)

#### 协程状态

例程也是有状态的,普通例程的状态等同于其内存。普通例程怎么记录时那个函数被执行的呢。

如下图

![](./resource/coro/05.png)

绿色部分便是保存例程状态的内存对象,其保存是是Function B的状态(函数执行栈)。

一个程序实际调用栈是这样的:

如下图