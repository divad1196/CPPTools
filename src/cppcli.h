#ifndef CPPTOOLS_CLI_H
#define CPPTOOLS_CLI_H

#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <algorithm>

// For debug
#include <iostream>
#include "string/conversion.h"

namespace Env {

    class MissingEnvVariable: public std::runtime_error {
        public:
            explicit MissingEnvVariable(const std::string& what_arg): runtime_error(what_arg){}
            explicit MissingEnvVariable(const char* what_arg): runtime_error(what_arg){}
    };

    template<typename T>
    T get(const char* name) {
        char* res = std::getenv(name);
        if(res == nullptr)
            throw MissingEnvVariable(std::string("Variable ") + name + " does not exist in environment");
        return Convert::from_string<T>(res);
    }

    template<typename T>
    T get(const char* name, const T& default_value) {
        char* res = std::getenv(name);
        if(res == nullptr)
            return default_value;
        return Convert::from_string<T>(res);
    }

    template<typename T>
    T get(const std::string& name) {
        return get<T>(name.c_str());
    }

    template<typename T>
    T get(const std::string& name, const T& default_value) {
        return get<T>(name.c_str(), default_value);
    }
};


namespace ArgTypes {
    class Abstract {
        public:
            void parse(const std::string& arg);
    };

    template<typename T>  // , char separator=','
    class List {
        public:
            void parse(const std::string& arg) {
                _values.push_back(Convert::from_string<T>(arg));
            }
        private:
            std::vector<T> _values;
    };

    class Int {
        public:
            void parse(const std::string& arg) {
                
            }
        private:
            int _value;

    };


};

#endif // CPPTOOLS_CLI_H