# CplusplusQuickGuide
一篇快速掌握基础C++的教程，最近在Linux下编程较多用到的C++知识有些许荒废了，这个旨在能够快速帮助自己回顾c++的面向对象基本知识。


### C++基础快速上手

[一.面向对象基础思想和类中的几大基础函数](doc/01.md)

[二.继承与多态基础](doc/02.md)

[三.多重继承基础](doc/03.md)

[四.虚函数,抽象和封装的基础](doc/04.md)

[五.友元基础](doc/05.md)

[六.C++的文件IO](doc/06.md)

[七.C++的泛型编程(模板)基础](doc/07.md)

[八.namespace命名空间基础](doc/08.md)


### 从底层原理探究C++

[一.虚拟内存,函数堆栈调用过程,编译链接详解--从底层来理解代码](doc/advance/a1.md)

有一部文章我全部以源代码+注释形式书写直接看源文件即可。只有关键部分会有专门文章总结。

[二.C++基础精髓](https://github.com/helintongh/CplusplusQuickGuide/tree/master/src/01CPP%E5%BF%85%E9%A1%BB%E6%8E%8C%E6%8F%A1%E7%9A%84%E5%9F%BA%E7%A1%80%E7%9F%A5%E8%AF%86%E7%B2%BE%E8%AE%B2)

- C++基础精髓依次讲述了C++函数知识,const关键字与指针,左值右值引用,以及C++的内存管理。

- 右值引用是C++减少默认函数调用,智能指针,move移动语义和forward类型完美转发的基石也是现代C++极其重要的特性。到了C++的优化中我会花大力气讲述右值引用带来的巨大提升。

- [什么是右值](doc/advance/a2.md)

[三.C++类的各种细节和原理](doc/advance/a3.md)

源文件在 [点此跳转](https://github.com/helintongh/CplusplusQuickGuide/tree/master/src/02%E7%B1%BB%E5%92%8C%E5%AF%B9%E8%B1%A1%E7%9A%84%E7%BB%86%E8%8A%82%E4%B8%8E%E5%8E%9F%E7%90%86)
为什么C++会有一些函数？赋值构造函数和拷贝构造函数解决了什么问题(浅拷贝)？ 构造函数,析构函数,拷贝构造函数,赋值构造函数,以及后续会讲到的move构造函数(这个学名叫move constructor,有的中文翻译为带右值引用参数的构造函数翻译的不行)

[四.函数模板](https://github.com/helintongh/CplusplusQuickGuide/tree/master/src/03%E6%A8%A1%E6%9D%BF%E7%BC%96%E7%A8%8B)

要明确模板的实例化,模板的实参推演,模板特例化,部分特例化。

[五.运算符重载](https://github.com/helintongh/CplusplusQuickGuide/tree/master/src/04%E8%BF%90%E7%AE%97%E7%AC%A6%E9%87%8D%E8%BD%BD)

### C++的优化以及C++11-20的新特性的探索

todo