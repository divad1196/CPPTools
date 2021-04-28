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
};


#endif  // CPPTOOLS_FUNCTION_H