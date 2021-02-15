#ifndef CPPTOOLS_STRING_MISC
#define CPPTOOLS_STRING_MISC

#include <algorithm>
#include <string>
#include <cctype>

template<typename CharT, typename StringType>
bool instring(CharT ch, const StringType& list) {
    auto last = std::end(list);
    return std::find(std::cbegin(list), last, ch) != last;
}

template<typename CharT>
bool instring(CharT ch, const CharT* list) {
    while(*list != '\0') {
        if(*list == ch)
            return true;
        ++list;
    }
    return false;
}

// Insensitive comparison
bool icomp(const std::string& a, const std::string& b) {
    if(a.length() != b.length())
        return false;
    for(size_t i = 0; i < a.length(); ++i) {
        if(tolower(a[i]) != tolower(b[i]))
            return false;
    }
    return true;
}

// Todo ?
// bool icomp(const std::string& a, const char* b) {}

#endif // CPPTOOLS_STRING_MISC