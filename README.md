# CplusplusQuickGuide
一篇快速掌握基础C++的教程，最近在Linux下编程较多用到的C++知识有些许荒废了，这个旨在能够快速帮助自己回顾c++的面向对象基本知识。

请先看C++的思维导图 ![C++基础](./resource/CPP_basic.md)

### C++基础快速上手

| C++基础上手教程                                      |                                         |
| ---------------------------------------------------- | --------------------------------------- |
| [一.面向对象基础思想和类中的几大基础函数](doc/01.md) | [二.继承与多态基础](doc/02.md)          |
| [三.多重继承基础](doc/03.md)                         | [四.虚函数,抽象和封装的基础](doc/04.md) |
| [五.友元基础](doc/05.md)                             | [六.C++的文件IO](doc/06.md)             |
| [七.C++的泛型编程(模板)基础](doc/07.md)              | [八.namespace命名空间基础](doc/08.md)   |

### 从底层原理探究C++

**知道了为什么?就知道了知识。**

有一部文章我全部以源代码+注释形式书写直接看源文件即可,看了示例代码与注释就能弄明白相应的知识点。只有关键部分会有专门文章总结。代码才是最好的老师。

[一.虚拟内存,函数堆栈调用过程,编译链接详解--从底层来理解代码](doc/advance/a1.md)

[二.C++基础精髓-源文件文件夹](https://github.com/helintongh/CplusplusQuickGuide/tree/master/src/01CPP%E5%BF%85%E9%A1%BB%E6%8E%8C%E6%8F%A1%E7%9A%84%E5%9F%BA%E7%A1%80%E7%9F%A5%E8%AF%86%E7%B2%BE%E8%AE%B2)

- C++基础精髓依次讲述了C++函数知识,const关键字与指针,左值右值引用,以及C++的内存管理。

- 右值引用是C++减少默认函数调用,智能指针,move移动语义和forward类型完美转发的基石也是现代C++极其重要的特性。到了C++的优化中我会花大力气讲述右值引用带来的巨大提升。

- [什么是右值](doc/advance/a2.md)

[三.C++类的各种细节和原理-源文件文件夹](doc/advance/a3.md)

源文件在 [点此跳转](https://github.com/helintongh/CplusplusQuickGuide/tree/master/src/02%E7%B1%BB%E5%92%8C%E5%AF%B9%E8%B1%A1%E7%9A%84%E7%BB%86%E8%8A%82%E4%B8%8E%E5%8E%9F%E7%90%86)
为什么C++会有这一些函数？赋值构造函数和拷贝构造函数解决了什么问题(浅拷贝)？ 构造函数,析构函数,拷贝构造函数,赋值构造函数,以及后续会讲到的move构造函数是为什么存在?(这个学名叫move constructor,有的中文翻译为带右值引用参数的构造函数这种翻译是不太好的)

[四.函数模板-源文件文件夹](https://github.com/helintongh/CplusplusQuickGuide/tree/master/src/03%E6%A8%A1%E6%9D%BF%E7%BC%96%E7%A8%8B)

要明确模板的实例化,模板的实参推演,模板特例化,部分特例化。 一文了解模板我实现了一个vector,这个vector没有迭代器,后面会实现带迭代器版本。 
[模板拾遗及实现一个vector](doc/advance/a4.md)

[五.运算符重载-源文件文件夹](https://github.com/helintongh/CplusplusQuickGuide/tree/master/src/04%E8%BF%90%E7%AE%97%E7%AC%A6%E9%87%8D%E8%BD%BD)

运算符重载有什么用?要明白运算符重载与泛型算法密切相关。
1. 泛型算法参数接收的都是迭代器,泛型算法往往是给所有容器用的全局函数,泛型算法有一套方法能够统一的遍历所有的容器的元素(通过迭代器)。迭代器一般实现为容器的内部嵌套类型,因为不同容器操作不同。
2. 而迭代器大量运用到了运算符重载。

[通过实现近乎完整String和迭代器失效以及new和delete重载来学习运算符重载](doc/advance/a5.md)

[六.继承与多态-源文件文件夹](https://github.com/helintongh/CplusplusQuickGuide/tree/master/src/05%E7%BB%A7%E6%89%BF%E5%92%8C%E5%A4%9A%E6%80%81)

[一文理解继承与多态](doc/advance/a6.md)

[七.多重继承-源文件夹](https://github.com/helintongh/CplusplusQuickGuide/tree/master/src/06%E5%A4%9A%E9%87%8D%E7%BB%A7%E6%89%BF)

[一文理解多继承与它的坑](doc/advance/a7.md)

[八.STL底层原理浅析及使用-源文件夹](https://github.com/helintongh/CplusplusQuickGuide/tree/master/src/07STL%E5%BA%93%E7%9A%84%E5%BA%95%E5%B1%82%E5%8E%9F%E7%90%86%E4%BB%A5%E5%8F%8A%E4%BD%BF%E7%94%A8)
stl没有什么好讲的关键构建知识图谱:顺序容器(vector,deque,list),容器适配器即底层是vector等容器的(stack,queue,priority_queue),关联容器(set,map,unordered_set,unordered_map)，近容器(string,bitset),迭代器和反向迭代器,函数对象,泛型算法

其中难以理解的就是函数对象,所谓函数对象就是重载了该()运算符的对象而已。

### C++的优化以及C++11-20的新特性的探索

[C++优化及右值引用-源文件夹](https://github.com/helintongh/CplusplusQuickGuide/tree/master/src/08%E4%BC%98%E5%8C%96%E5%AF%B9%E8%B1%A1%E9%AB%98%E6%95%88CPP%E7%BC%96%E7%A8%8B)
[C++的优化以及右值引用的价值](doc/senior/s1.md) -- 讲解了move和forward,实现了更加完整的vector

[智能指针源文件夹](https://github.com/helintongh/CplusplusQuickGuide/tree/master/src/09%E6%99%BA%E8%83%BD%E6%8C%87%E9%92%88)
[理解智能指针](doc/senior/s2.md)

[function-bind绑定器-lambda-源文件夹](https://github.com/helintongh/CplusplusQuickGuide/tree/master/src/10bind%E7%BB%91%E5%AE%9A%E5%99%A8%E5%92%8Cfunction%E5%87%BD%E6%95%B0%E5%AF%B9%E8%B1%A1)
[C++的函数对象,绑定器,lambda表达式](doc/senior/s3.md)
[lambda表达式详解](doc/senior/s4.md)

[thread库-源文件夹](https://github.com/helintongh/CplusplusQuickGuide/blob/master/src/11Thread%E5%BA%93/01_1cpp_thread%E7%B1%BB%E7%BC%96%E5%86%99%E5%A4%9A%E7%BA%BF%E7%A8%8B.cpp)