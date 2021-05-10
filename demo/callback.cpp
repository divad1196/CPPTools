#include<cstdlib>
#include<iostream>
#include<string>
#include<future>

#include "callback.h"

int main() {

    Wrapper<int> a(0,
        [](const int& value){ return value / 2; },
        [](const int& new_value){ return new_value * 4;}
    );

    std::cout << "Start" << std::endl;
    std::cout << a.get() << std::endl;
    a.set(10);
    std::cout << a.get() << std::endl;
    a = a * 3;
    std::cout << a << std::endl;



    Wrapper<std::string> t("",
        [](const std::string& value){ return value + " end"; },
        [](const std::string& new_value){ return new_value + " ";}
    );

    std::cout << (std::string)t << std::endl;
    // std::cout << (t = "hello") << std::endl;


    int tmp = 0;

    Subject<int> b(0);
    b.subscribe([&tmp](const int& value) { tmp = value; });
    b.subscribe([](const int& value) { std::cout << "value changed to " << value << std::endl; });

    std::cout << tmp << std::endl;
    b.set(9);
    std::cout << tmp << std::endl;

    Interval interval(500);
    interval.runFor([](){
        std::cout << "hello world" << std::endl;
    }, 1000);

    int count = 0;
    Debounce dbounce(200);
    while (count < 5) {
        dbounce && (count += 1) && (
            std::cout << count << std::endl
        );
    }

    count = 0;
    while (count < 5) {
        dbounce && (count += 1) && (
            std::cout << "foo" << std::endl
        );
        dbounce && (count += 1) && (
            std::cout << "bar" << std::endl
        );
        dbounce && (count += 1) && (
            std::cout << "hello" << std::endl
        );
        dbounce && (count += 1) && (
            std::cout << "world" << std::endl
        );
    }

    std::vector<int> list {1, 2, 3, 4, 5, 6};
    Aggregate<int, int> ag(0, [](const int& aggr, const int& value){ return aggr + value; });
    for(int value: list) {
        std::cout << ag.next(value) << std::endl;
    }

    std::string texte;
    ThreadedWrapper<int> tdwrapper(
        0,
        [&](const int& value){
            std::cout << value << std::endl;
            return value;
        }
    );

    std::async([&tdwrapper](){
        if(tdwrapper % 2 == 0)
            tdwrapper = tdwrapper + 1;
    });

    std::async([&tdwrapper](){
        if(tdwrapper % 2 != 0)
            tdwrapper = tdwrapper + 1;
    });


    return EXIT_SUCCESS;
}