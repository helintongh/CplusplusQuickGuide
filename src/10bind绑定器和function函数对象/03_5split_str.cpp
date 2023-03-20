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