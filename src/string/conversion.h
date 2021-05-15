#ifndef CPPTOOLS_STRING_CONVERT
#define CPPTOOLS_STRING_CONVERT

#include <cctype>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "base.h"
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
    void split_foreach(const std::string& str, std::function<void(T)> callback, char sep=',') {
        auto start = str.begin();
        auto end = std::find(start, str.end(), sep);
        if(start != end)
            callback(
                from_string<T>(
                    std::string(start, end)
                )
            );
        while(end != str.end()) {
            start = ++end;
            end = std::find(start, str.end(), sep);
            callback(
                from_string<T>(
                    std::string(start, end)
                )
            );
        };

        return res;
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


#endif // CPPTOOLS_STRING_CONVERT