#include <cstdlib>
#include <iostream>


#include "cppcli.h"




int main(int argc, char* argv[]) {
    auto res = Convert::split<int>("543, 34, 12");
    for(int i: res) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return EXIT_SUCCESS;
}

