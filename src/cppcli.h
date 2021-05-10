#ifndef CPPTOOLS_CLI_H
#define CPPTOOLS_CLI_H

#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <algorithm>

#include "cppenv.h"

// For debug
#include <iostream>
#include "string/conversion.h"



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