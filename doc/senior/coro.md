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

普通的程序(多线程或多进程)就只支持两种操作:: Invoke/Finalize

调用如下图:

![](./resource/coro/02.png)

