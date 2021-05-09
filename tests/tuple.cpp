#include <cstdlib>
#include <iostream>


#include "../src/tuple.h"




int main(int argc, char* argv[]) {
    auto a = std::index_sequence<1,4,5>();
    auto b = cond_extends<true, 3>(a);
    auto c = cond_extends<false, 3>(a);

    std::tuple<int, int> d{};
    auto e = extends(d, std::string("hello"), 5.6);
    auto f = cond_extends<true>(d, std::string("hello"), 5.6);
    auto g = cond_extends<false>(d, std::string("hello"), 5.6);
    print_tuple(d);
    print_tuple(e);
    print_tuple(f);
    print_tuple(g);

    auto x = std::make_tuple(3, 4, std::string("foo"), 5, 6, std::string("bar"));
    auto seq = cond_index_seq<std::is_integral>(x);
    auto sub = extract(x, seq);
    auto sub2 = cond_extract<std::is_integral>(x);
    print_tuple(x);
    print_tuple(sub);
    print_tuple(sub2);

    return EXIT_SUCCESS;
}

