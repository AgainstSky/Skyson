#include <iostream>
#include <string>
#include "Skyson.h"

using namespace std;
using namespace skyson;
int main() {
    string jsonStr = "{\n"
                     "    \"str\":\"valu,e\",\n"
                     "    \"num\":1,\"bool\":true,\n"
                     "    \"double\":1.1,\n"
                     "    \"object\":{\n"
                     "        \"array\":[\n"
                     "            \"abc\",\"cbd\",1,2\n"
                     "        ]\n"
                     "    }\n"
                     "}";
    auto jobj = parse(jsonStr);
    return 0;
}
