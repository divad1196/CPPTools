#ifndef CPPTOOLS_FUNCTION_H
#define CPPTOOLS_FUNCTION_H

#include <tuple>

template<typename S>
struct Signature;

template<typename R, typename... Args>
struct Signature<R(Args...)>
{
    using return_type = R;
    using argument_type = std::tuple<Args...>;
    inline static const size_t param_count = std::tuple_size<
        argument_type
    >::value;
    inline static const std::integer_sequence indexes = std::make_index_sequence<param_count>{};
};

// Support for std::function too
#include <functional>
template<typename R, typename... Args>
struct Signature<std::function<R(Args...)>>
{
    using return_type = R;
    using argument_type = std::tuple<Args...>;
    inline static const size_t param_count = std::tuple_size<
        argument_type
    >::value;
};


#endif  // CPPTOOLS_FUNCTION_H