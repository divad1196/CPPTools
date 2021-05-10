#include<cstdlib>
#include<string>
#include<iostream>
#include <iomanip>

#include "tools.h"

int main() {

    std::string a = "   test  ";
    std::cout << strip(a) << " <= " << a << std::endl;
    std::cout << lstrip(a) << " <= " << a << std::endl;
    std::cout << rstrip(a) << " <= " << a << std::endl;



    std::string b = "aaabbbbaatestacccccaa";
    istrip<std::string>(b, std::string("abc").c_str());
    std::cout << b << std::endl;

    std::cout << std::boolalpha;
    std::cout << is_basic_string<std::string>::value << std::endl;
    // std::cout << is_basic_string<std::iostream>::value << std::endl;


    return EXIT_SUCCESS;
}