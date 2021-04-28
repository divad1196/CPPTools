#include <cstdlib>
#include <iostream>
#include <iomanip>

#include <map>
#include <string>
#include <tuple>
#include <functional>

#include <cctype>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <tuple>
#include <type_traits>

bool icomp(const std::string& a, const std::string& b) {
    if(a.length() != b.length())
        return false;
    for(size_t i = 0; i < a.length(); ++i) {
        if(tolower(a[i]) != tolower(b[i]))
            return false;
    }
    return true;
}

namespace Convert {

    class ConversionError: public std::runtime_error {
        public:
            explicit ConversionError(const std::string& what_arg): runtime_error(what_arg){}
            explicit ConversionError(const char* what_arg): runtime_error(what_arg){}
    };
    class EmptyStringError: public ConversionError {
        public:
            EmptyStringError(): ConversionError("Can not convert an empty string"){}
    };

    void check_empty_string(const std::string& str) {
        if(str.empty())
            throw EmptyStringError();
    }

    template<typename T>
    std::string to_string(const T& str) {
        return std::to_string(str);
    }

    std::string to_string(const char* str) {
        return std::string(str);
    }

    template<typename T>
    T from_string(const std::string& str) {
        T tmp;
        std::stringstream stream;
        stream << str;
        stream >> tmp;
        return tmp;
    }

    template<>
    int from_string<int>(const std::string& str) {
        return std::stoi(str);
    }

    template<>
    double from_string<double>(const std::string& str) {
        return std::stod(str);
    }

    template<>
    bool from_string<bool>(const std::string& str) {
        check_empty_string(str);
        if(isdigit(str[0]))
            return bool(from_string<int>(str));
        if(icomp(str, "true"))
            return true;
        if(icomp(str, "false"))
            return false;
        throw ConversionError(std::string("Could not convert string '") + str + "' to boolean");
    }

    template<typename T>
    std::vector<T> split(const std::string& str, char sep=',') {
        auto start = str.begin();
        auto end = std::find(start, str.end(), sep);
        std::vector<T> res;
        if(start != end)
            res.push_back(
                from_string<T>(
                    std::string(start, end)
                )
            );
        while(end != str.end()) {
            start = ++end;
            end = std::find(start, str.end(), sep);
            res.push_back(
                from_string<T>(
                    std::string(start, end)
                )
            );
        };

        return res;
    }

};

template<typename S>
struct Signature;

template<typename R, typename... Args>
struct Signature<R(Args...)>
{
    using return_type = R;
    using argument_type = std::tuple<Args...>;
};

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

int myfunc(int a, int b) {
    return a + b;
}

void myfunc2(bool a, bool b) {
    std::cout << std::boolalpha
        << a << ' '
        << b << ' '
        << (a && b) << ' '
        << (a || b) << ' '
        << std::endl;
}

int main() {
    std::cout << "test" << std::endl;
    std::map<std::string, std::string> m;
    m["foo"] = "3";
    m["bar"] = "5";
    m["hello"] = "3";
    m["world"] = "false";
    Caller caller(myfunc, "foo", "bar");
    std::cout << caller.call(m) << std::endl;
    std::cout << caller._param_count << std::endl;

    Caller(myfunc2, "hello", "world")(m);

    return EXIT_SUCCESS;
}
