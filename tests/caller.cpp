#include <cstdlib>
#include <iostream>
#include <iomanip>

#include <map>
#include <string>

#include "../src/caller.h"

int myfunc(int a, int b) {
    return a + b;
}

void myfunc2(bool a, bool b) {
    std::cout << std::boolalpha
        << a << ' '
        << b << ' '
        << (a && b) << ' '
        << (a || b) << ' '
        << std::endl;
}

int main() {
    std::cout << "test" << std::endl;
    std::cout << Signature<std::function<decltype(myfunc)>>::param_count << std::endl;
    std::map<std::string, std::string> m;
    m["foo"] = "3";
    m["bar"] = "5";
    m["hello"] = "3";
    m["world"] = "false";
    Caller caller(myfunc, "foo", "bar");
    std::cout << caller.call(m) << std::endl;
    std::cout << caller.param_count << std::endl;

    Caller(myfunc2, "hello", "world")(m);

    return EXIT_SUCCESS;
}
