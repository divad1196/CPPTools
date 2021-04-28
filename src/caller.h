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


template<typename Callable, typename... Keys>
class Caller {

    using signature = Signature<Callable>;
    using Map = std::map<std::string, std::string>;

    public:
        using Func = std::function<Callable>;
        Caller(const Callable& f, Keys... keys):
            _inner(f),
            _keys(std::make_tuple(keys...)),
            _param_count(std::tuple_size<
                                typename signature::argument_type
                            >::value)
        {}

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

        typename signature::return_type
        call(Map params) {
            return call_impl(
                params,
                std::make_index_sequence<
                    std::tuple_size<
                        typename signature::argument_type
                    >::value
                >{}
            );
        }

        typename signature::return_type
        operator() (Map params) {
            return call(params);
        }

    private:
        const Func _inner;
        std::tuple<Keys...> _keys;
    public:
        const size_t _param_count;

};


#endif  // CPPTOOLS_CALLER_H