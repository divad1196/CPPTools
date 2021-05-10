#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../cpptools.h"


TEST_CASE( "Extraction" ) {
    auto x = std::make_tuple(3, 4, std::string("foo"), 5, 6, std::string("bar"));
    auto sub = cond_extract<std::is_integral>(x);
    CHECK( sub == std::make_tuple(3, 4, 5, 6) );

    const auto& [i, j, k] = extract<1, 2, 5>(x);
    CHECK( i == 4);
    CHECK( j == std::string("foo"));
    CHECK( k == std::string("bar"));


    auto m = extract<1, 2, 5>(x);
    auto n = slice<1, 2, 5>(x);
    CHECK( std::get<0>(m) == 4);
    CHECK( std::get<0>(n) == 4);
    std::get<1>(x) += 3;
    CHECK( std::get<0>(m) == 4);
    CHECK( std::get<0>(n) == 7);
}