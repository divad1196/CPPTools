#include<cstdlib>
#include<string>
#include<iostream>
#include <iomanip>

#include "../src/cppenv.h"

int main() {
    std::string a = Env::get<std::string>("USERNAME");
    std::cout << a << std::endl;

    Env::set("USERNAME", "help", false);
    std::cout << "ok" << std::endl;
    a = Env::get<std::string>("USERNAME");
    std::cout << a << std::endl;

    Env::set("USERNAME", "help");
    a = Env::get<std::string>("USERNAME");
    std::cout << a << std::endl;


    Env::unset("USERNAME");
    a = Env::get<std::string>("USERNAME", "default");
    std::cout << a << std::endl;

    Env::set("MYTEST", "true");
    bool b = Env::get<bool>("MYTEST");
    std::cout << std::boolalpha << b << std::endl;

    Env::set("MYTEST", "false");
    b = Env::get<bool>("MYTEST");
    std::cout << std::boolalpha << b << std::endl;

    Env::set("MYTEST", "something");
    try {
        b = Env::get<bool>("MYTEST");
    } catch (...) {
        std::cout << "Error correctly thrown" << std::endl;
    }

    Env::set("MYTEST", 1);
    b = Env::get<bool>("MYTEST");
    std::cout << std::boolalpha << b << std::endl;


    Env::set("MYTEST", "32,57,98");  // White space can not be used here
    auto l = Convert::split<int>(Env::get("MYTEST"));
    for(int i: l) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}