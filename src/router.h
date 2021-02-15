#ifndef CPPTOOLS_ROUTER
#define CPPTOOLS_ROUTER

#include<tuple>
#include<iostream>
#include<functional>


/*
 * Trying to add support for C++14
 * https://sourceforge.net/p/predef/wiki/Standards/
 * https://en.cppreference.com/w/cpp/experimental/apply
 */
#if !defined(__cplusplus) || __cplusplus < 201703L
#include <experimental/tuple>
namespace std {
    using std::experimental::fundamentals_v1::apply;
}
#endif


template<typename... T>
std::tuple<T...> scan(const std::string& text, const std::string& pattern) {
    std::tuple<T...> values;

    std::apply(
        [&](T&... Args) {
            sscanf(text.c_str(), pattern.c_str(), &Args...);
        },
        values
    );

    return values;
}

template<typename... T>
class OLDScanner {
    std::tuple<T...> operator()(const std::string& text, const std::string& pattern) {
        return scan<T...>(text, pattern);
    }
};


template<template<typename Text, typename Pattern, typename... Scannable> typename _Scanner>
class Scanner {

    template<typename... E>
    class Extras {
        public:
            template<typename... T>
            class Route {
                public:
                    using Callable = std::function<void(T..., E...)>;
                    Route(const std::string& pattern, const Callable& callable): _pattern(pattern), _callable(callable)
                    {}

                    void operator() (const std::string& text, E... extras) {
                        std::tuple<T...> values = scan<T...>(text, _pattern);

                        std::apply(
                            [&](T... args){
                                _callable(args..., extras...);
                            },
                            values
                        );
                    }

                private:
                    std::string _pattern;
                    Callable _callable;
            };
    };
};

// Without Extra Parameters
using Extras = Scanner<OLDScanner>;

template<typename... T>
using Route = Extras<>::Route<T...>;

// template<typename... T>
// Route<T...> make_route(const std::string& pattern, std::function<void(T...)> callable) {
//     return Route<T...>(pattern, callable);
// }


#endif // CPPTOOLS_ROUTER