#ifndef CPPTOOLS_ENVIRONMENT
#define CPPTOOLS_ENVIRONMENT

#include <string>
#include <cstdlib>


#include "string/conversion.h"

// For debug
#include <iostream>

namespace Env {

    class MissingEnvVariable: public std::runtime_error {
        public:
            explicit MissingEnvVariable(const std::string& what_arg): runtime_error(what_arg){}
            explicit MissingEnvVariable(const char* what_arg): runtime_error(what_arg){}
    };

    template<typename T=std::string>
    T get(const char* name) {
        char* res = std::getenv(name);
        if(res == nullptr)
            throw MissingEnvVariable(std::string("Variable ") + name + " does not exist in environment");
        return Convert::from_string<T>(res);
    }

    template<typename T=std::string>
    T get(const char* name, const T& default_value) {
        char* res = std::getenv(name);
        if(res == nullptr)
            return default_value;
        return Convert::from_string<T>(res);
    }

    template<typename T=std::string>
    T get(const std::string& name) {
        return get<T>(name.c_str());
    }

    template<typename T=std::string>
    T get(const std::string& name, const T& default_value) {
        return get<T>(name.c_str(), default_value);
    }

    template<typename T>
    bool set(const char* name, const T& value, bool overwrite=true) {
        return setenv(name, Convert::to_string<T>(value).c_str(), overwrite) == 0;
    }
    template<typename T>
    bool set(const std::string& name, const T& value, bool overwrite=true) {
        return set(name.c_str(), Convert::to_string<T>(value), overwrite) == 0;
    }
    bool set(const char* name, const char* value, bool overwrite=true) {
        return setenv(name, value, overwrite) == 0;
    }
    bool set(const std::string& name, const char* value, bool overwrite=true) {
        return set(name.c_str(), value, overwrite) == 0;
    }

    bool unset(const char* name) {
        return unsetenv(name) == 0;
    }
    bool unset(const std::string& name) {
        return unsetenv(name.c_str()) == 0;
    }
};

#endif // CPPTOOLS_ENVIRONMENT