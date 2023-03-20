## 实战:字符串分割

我将分别采用lamda表达式和function以及普通函数来实现字符串分割函数,以此来理解C++的函数式编程

先来看一个简单的例子。

### 简单版

!!!

    "This is a statement"

使用C++将这个字符串分割成四个子字符串:"This", "is", "a", "statement".

```c++
#include <iostream>
using std::cout;
#include <iterator>
using std::istream_iterator; using std::ostream_iterator;
#include <string>
using std::string;
#include <sstream>
using std::istringstream;
#include <algorithm>
using std::copy;

int main()
{
    string str("This is a statement");
    istringstream iss(str), end;
    copy(istream_iterator<string>(iss), istream_iterator<string>(end), ostream_iterator<string>(cout, "\n"));
    return 0;
}
```

很清晰的代码

### 工程实用版

上面的方法虽然简洁,但是仅能够按空格分隔,在实际工程中,显然是没太大用处的,抽出一个`split`函数还是很有必要的。

```c++
#include <iostream>
using std::cout; using std::getline;
#include <iterator>
using std::ostream_iterator;
#include <string>
using std::string;
#include <sstream>
using std::istringstream;
#include <vector>
using std::vector;
#include <algorithm>
using std::copy;

vector<string> &split(const string &str, char delim, vector<string> &elems, 
    bool skip_empty = true) {
    istringstream iss(str);
    for (string item; getline(iss, item, delim); )
        if (skip_empty && item.empty()) continue;
        else elems.push_back(item);
    return elems;
}

int main()
{
    string str("Windows,Linux,,MacOS,");
    vector<string> result;
    split(str, ',', result);
    copy(result.begin(), result.end(), ostream_iterator<string>(cout, "\n"));
    return 0;
}
```

上述代码输出:

```
Windows
Linux
MacOS
```

这样我们不仅可以用别的字符来做分隔,还可以选择跳过空白字符串,如我故意在 Linux 和 MacOS 之间放了两个相邻的 `,,`，若不做处理和判断的话，就会多分割出一个空白字符来。

### 继续改进版

上面这样，还有一个限制未解决，即如果我想按多种字符来分隔呢？如按照 `,,|`以及空格，来分割字符串。

可以利用`find_first_of`来实现。

```c++
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <iostream>

vector<string> &split( const string &str, const string &delimiters, vector<string> &elems, 
    bool skip_empty = true ) {
    string::size_type pos, prev = 0;
    while ( ( pos = str.find_first_of(delimiters, prev) ) != string::npos ) {
        if ( pos > prev ) {
            if ( skip_empty && 1 == pos - prev ) break;
            elems.emplace_back( str, prev, pos - prev );
        }
        prev = pos + 1;
    }
    if ( prev < str.size() ) elems.emplace_back( str, prev, str.size() - prev );
    return elems;
}

int main()
{
    string str( "Windows,Linux||MacOS All" );
    vector<string> result;
    for ( const auto &s : split( str, ",| ", result ) )
        std::cout << s << " ";
    std::cout << std::endl;
}
```

上述代码输出:

```
Windows Linux MacOS All
```

### 使用function+lambda来实现字符串分割

注意这里使用了auto语句自动确定变量类型,这里的split其实就成为了一个函数对象。

这里的auto完全可以用function来替代。下面的代码`std::function<vector<string>&(const string &,const string &,vector<string> &,bool skip_empty)>`用auto就可以代替。

```c++
std::function<vector<string>&(const string &,const string &,vector<string> &,bool skip_empty)> split = [](const string &str, 
                const string &delimiters, 
                vector<string> &elems, 
                bool skip_empty) -> vector<string>& {
        // 略
    };
// 上面的split函数和下面的split函数这两个函数是完全等价的
auto split = [](const string &str, 
                const string &delimiters, 
                vector<string> &elems, 
                bool skip_empty) -> vector<string>& {
        // 略
    };
```

```c++
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <iostream>
#include <functional>

int main()
{
    string str( "Windows,Linux||MacOS All" );
    // lambda表达式实现字符串分割,该split其实是一个function
    // auto等价于std::function<vector<string>&(const string &,const string &,vector<string> &,bool skip_empty)>
    auto split = [](const string &str, 
                const string &delimiters, 
                vector<string> &elems, 
                bool skip_empty) -> vector<string>& {
        string::size_type pos, prev = 0;
        while ( ( pos = str.find_first_of(delimiters, prev) ) != string::npos ) {
            if ( pos > prev ) {
                if ( skip_empty && 1 == pos - prev ) break;
                elems.emplace_back( str, prev, pos - prev );
            }
            prev = pos + 1;
        }
        if ( prev < str.size() ) elems.emplace_back( str, prev, str.size() - prev );
        return elems;
    };

    vector<string> result;
    split(str, ",| ", result, true);

    for (auto i : result)
        std::cout << i << std::endl;
}
```

[代码路径](../../src/10bind绑定器和function函数对象/03_5split_str.cpp)

上述代码输出:

```
Windows
Linux
MacOS
All
```

下面用`function`以及`bind`来写一个等价功能,可以看到auto是更加简洁的实现。

```c++
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <iostream>
#include <functional>

vector<string> &split( const string &str, const string &delimiters, vector<string> &elems, 
    bool skip_empty) {
    string::size_type pos, prev = 0;
    while ( ( pos = str.find_first_of(delimiters, prev) ) != string::npos ) {
        if ( pos > prev ) {
            if ( skip_empty && 1 == pos - prev ) break;
            elems.emplace_back( str, prev, pos - prev );
        }
        prev = pos + 1;
    }
    if ( prev < str.size() ) elems.emplace_back( str, prev, str.size() - prev );
    return elems;
}

int main()
{
    string str( "Windows,Linux||MacOS All" );
    std::function<vector<string>&(const string &,const string &,vector<string> &,bool skip_empty)> func = bind(split, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
    vector<string> result;
    func(str, ",| ", result, false);
    for (auto i : result)
        std::cout << i << std::endl;
}
```

以上就是整个的分割字符串技术。

## 总结

function和bind以及lambda本质是一个东西都是函数对象，在具体一点就是C++中的对象实现了`()`运行符。

下面实现一个自己的function来看一下function底层究竟是什么:


关注核心代码:

其中`...`表示可变参指参数不固定。可以看到该类只实现了`()`运算符重载。这就是函数对象的底层原理。

```c++
template<typename R, typename... A>
class myfunction<R(A...)>
{
public:
	using PFUNC = R(*)(A...);
	myfunction(PFUNC pfunc) :_pfunc(pfunc) {}
	R operator()(A... arg)
	{
		return _pfunc(arg...); 
	}
private:
	PFUNC _pfunc;
};
```

完整代码, [源代码](../../src/10bind绑定器和function函数对象/02_4function的原理.cpp)

```c++
#include <iostream>
#include <typeinfo>
#include <string>
#include <functional>
using namespace std;

/*
function函数对象类型的实现原理
*/
void hello(string str) { cout << str << endl; }
int sum(int a, int b) { return a + b; }
///////////////////////////////////////////////
template<typename Fty>
class myfunction {};
/*
	... A 表示是可变参数,表示形参个数不一定多少个
*/
template<typename R, typename... A>
class myfunction<R(A...)>
{
public:
	using PFUNC = R(*)(A...);
	myfunction(PFUNC pfunc) :_pfunc(pfunc) {}
	R operator()(A... arg)
	{
		return _pfunc(arg...); 
	}
private:
	PFUNC _pfunc;
};

int main()
{
	myfunction<void(string)> func1(hello);
	func1("hello world!"); // func1.operator()("hello world!")

	myfunction<int(int, int)> func2(sum);
	cout << func2(10, 20) << endl;
	return 0;
}
```