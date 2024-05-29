#include <iostream>
#include "someip.h"

int main(){
    someip::net::message msg;
    std::map<std::string , int> m;
    m["Hello"] = 3;
    m["Bye"] = 4;
    msg << m;
    std::map<std::string, int> m2;
    msg >> m;
    return 0;
}