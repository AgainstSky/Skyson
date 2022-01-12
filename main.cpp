#include <iostream>
#include <string>
#include <sstream>
#include "Skyson.h"

using namespace std;
using namespace skyson;
void f(stringstream & ss){
    char c ;
    while (ss.get(c)){

        if (c=='z'){
            ss.seekg(-1,ios_base::cur);
            break;
        } else{
            cout<<c<<endl;
        }
    }
}
int main() {
//    string str ="abcdzefgzddfaf";
//    stringstream ss(str);
//    char c ;
//    while (ss.get(c)){
//        cout<<c<<endl;
//        f(ss);
//    }
    string jsonStr = "{\"str\":\"val中文支持\",\n  ,,\"null\":null,\"bool\":true}";
    auto jobj = parse(jsonStr);
    string str="str";
    JsonObject * childJson = static_cast<JsonObject * >(jobj->get(str));
    int a=0;
    auto strObj = childJson->getStr();
    cout<<*strObj<<endl;
    return 0;
}
