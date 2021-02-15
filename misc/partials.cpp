#include <cstdlib>
#include <iostream>
#include <functional>


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



// https://stackoverflow.com/questions/9065081/how-do-i-get-the-argument-types-of-a-function-pointer-in-a-variadic-template-cla
template<typename T>
struct function_traits;

template<typename R, typename ...Args>
struct function_traits<std::function<R(Args...)>>
{
    static const size_t nargs = sizeof...(Args);

    typedef R result_type;

    template <size_t i>
    struct arg
    {
        typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
    };
};

template<typename Func, typename... T>
Class partials {
    partials(const Func& func, T... args): _func$(func), _args(args) {}

    template<
    auto operator()

    private:
        const Func _func;
        const std::tuple<T...> _args;
}



int main() {


    return EXIT_SUCCESS;
}
