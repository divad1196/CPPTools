#include<cstdlib>

#include<tuple>
#include<iostream>

#include "router.h"

template<typename... Ts>
std::ostream& operator<<(std::ostream& os, std::tuple<Ts...> const& theTuple)
{
    std::apply
    (
        [&os](Ts const&... tupleArgs)
        {
            os << '[';
            std::size_t n{0};
            ((os << tupleArgs << (++n != sizeof...(Ts) ? ", " : "")), ...);
            os << ']';
        }, theTuple
    );
    return os;
}

template <typename... T>
int sum(T... vals) {
    return (vals + ...);
}


int main(int argc, char* argv[]) {

    std::string text(argc > 1 ? argv[1] : "");
    for(size_t i = 2; i < size_t(argc); ++i) {
        text += " ";
        text += argv[i];
    }

    Extras<int>::Route<int, int, float> route(
        "hello %d world %d final %f",
        [](int a, int b, float c, int extra) {
            std::cout << a << " - " << b  << " " << c << std::endl;
            std::cout << extra << std::endl;
    });


    Route<int, int, float> route2(
        "hello %d world %d final %f",
        [](int a, int b, float c) {
            std::cout << a << " - " << b  << " " << c << std::endl;
    });


    // auto route = make_route<int, int, float>(
    //     "hello %d world %d final %f",
    //     [](int a, int b, float c) {
    //         std::cout << a << " - " << b  << " " << c << std::endl;
    // });

    // route("hello 52 world 34 final 9.0");
    route(text, 5);
    route2(text);

    return 0;
}

