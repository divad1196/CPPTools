#ifndef CPPTOOLS_CALLER_H
#define CPPTOOLS_CALLER_H

#include <cstdlib>
#include <iostream>
#include <iomanip>

#include <map>
#include <string>
#include <tuple>
#include <functional>

#include "function.h"
#include "string.h"

// It currently uses class type deduction, which makes it usable only for C++17 and above

/*
    TODO:
    1. Make it able to use other structure than std::map<std::string, std::string>
       In fact, the struct itself must be able to return a casted value
       class MyMap;
       MyMap m;
       m.get<int>("key");  // or
       get<int>(m, "key");

*/

template<typename Callable, typename... Keys>
class Caller {

    using signature = Signature<Callable>;
    using Map = std::map<std::string, std::string>;

    template<std::size_t... Is>
    typename signature::return_type
    call_impl(
        Map params,
        std::index_sequence<Is...>
    ) {
        using types = typename signature::argument_type;

        types arguments = std::make_tuple(
            (Convert::from_string<typename std::tuple_element<Is, types>::type>(
                params.at(
                    std::get<Is>(_keys)
                )
            ))...
        );
        return std::apply(_inner, arguments);
    }

    public:
        // Could use signature::param_count instead, 
        // But we should ensure that signature::param_count == sizeof...(Keys)
        inline static const size_t param_count = sizeof...(Keys);
        /*inline static const size_t param_count = std::tuple_size<
                                typename signature::argument_type
                            >::value;
        */
        using Func = std::function<Callable>;
        Caller(const Callable& f, Keys... keys):
            _inner(f),
            _keys(std::make_tuple(keys...))
        {}


        typename signature::return_type
        call(Map params) {
            return call_impl(
                params,
                signature::indexes
            );
        }

        typename signature::return_type
        operator() (Map params) {
            return call(params);
        }

    private:
        const Func _inner;
        std::tuple<Keys...> _keys;
};


#endif  // CPPTOOLS_CALLER_H