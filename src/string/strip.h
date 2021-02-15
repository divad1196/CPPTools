#ifndef CPPTOOLS_STRING_STRIP
#define CPPTOOLS_STRING_STRIP

#include <algorithm>
#include <type_traits>
#include <functional>
#include <cctype>
#include <locale>

#include "base.h"

/*
template<typename T>
using basic_string_type = typename T::value_type;

template<typename T>
using basic_string_type = std::false_type;*/

// https://en.wikibooks.org/wiki/More_C++_Idioms/Member_Detector
template<typename T>
using is_basic_string = std::is_same<std::basic_string<typename T::value_type>, T>;

/*template<typename T>
using is_basic_string = std::false_type;*/


template<typename T>
using StripCondition = std::function<bool(T)>;


// Generic stripping

template<typename T, typename CharT>
static inline void ilstrip(T& s, const StripCondition<CharT>& condition) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [&condition](CharT ch){return !condition(ch);}));
}

template<typename T>
static inline void ilstrip(T& s, const StripCondition<typename T::value_type>& condition) {
    ilstrip<T, typename T::value_type>(s, condition);
}

template<typename T, typename CharT>
static inline void irstrip(T& s, const StripCondition<CharT>& condition) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [&condition](CharT ch){return !condition(ch);}).base(), s.end());
}

template<typename T>
static inline void irstrip(T& s, const StripCondition<typename T::value_type>& condition) {
    irstrip<T, typename T::value_type>(s, condition);
}


template<typename T, typename CharT>
static inline void istrip(T& s, const StripCondition<CharT>& condition) {
    ilstrip<T, CharT>(s, condition);
    irstrip<T, CharT>(s, condition);
}

template<typename T>
static inline void istrip(T& s, const StripCondition<typename T::value_type>& condition) {
    istrip<T, typename T::value_type>(s, condition);
}

template<typename T, typename CharT>
static inline T lstrip(T s, const StripCondition<CharT>& condition) {
    ilstrip<T, CharT>(s, condition);
    return s;
}

template<typename T>
static inline T lstrip(T s, const StripCondition<typename T::value_type>& condition) {
    ilstrip<T, typename T::value_type>(s, condition);
    return s;
}

template<typename T, typename CharT>
static inline T rstrip(T s, const StripCondition<CharT>& condition) {
    irstrip<T, CharT>(s, condition);
    return s;
}

template<typename T>
static inline T rstrip(T s, const StripCondition<typename T::value_type>& condition) {
    irstrip<T, typename T::value_type>(s, condition);
    return s;
}

template<typename T, typename CharT>
static inline T strip(T s, const StripCondition<CharT>& condition) {
    istrip<T, CharT>(s, condition);
    return s;
}

template<typename T>
static inline T strip(T s, const StripCondition<typename T::value_type>& condition) {
    istrip<T, typename T::value_type>(s, condition);
    return s;
}

// Without condition

template<typename T, typename CharT>
static inline void ilstrip(T& s) {
    ilstrip<T, CharT>(s, [](CharT ch){return std::isspace(ch);});
}

template<typename T>
static inline void ilstrip(T& s) {
    ilstrip<T, typename T::value_type>(s);
}

template<typename T, typename CharT>
static inline void irstrip(T& s) {
    irstrip<T, CharT>(s, [](CharT ch){return std::isspace(ch);});
}

template<typename T>
static inline void irstrip(T& s) {
    irstrip<T, typename T::value_type>(s);
}

template<typename T, typename CharT>
static inline void istrip(T& s) {
    istrip<T, CharT>(s, [](CharT ch){return std::isspace(ch);});
}

template<typename T>
static inline void istrip(T& s) {
    istrip<T, typename T::value_type>(s);
}

template<typename T, typename CharT>
static inline T lstrip(const T& s) {
    return lstrip<T, CharT>(s, [](CharT ch){return std::isspace(ch);});
}

template<typename T>
static inline T lstrip(const T& s) {
    return lstrip<T, typename T::value_type>(s, [](typename T::value_type ch){return std::isspace(ch);});
}

template<typename T, typename CharT>
static inline T rstrip(const T& s) {
    return rstrip<T, CharT>(s, [](CharT ch){return std::isspace(ch);});
}

template<typename T>
static inline T rstrip(const T& s) {
    return rstrip<T, typename T::value_type>(s, [](typename T::value_type ch){return std::isspace(ch);});
}

template<typename T, typename CharT>
static inline T strip(const T& s) {
    return strip<T, CharT>(s, [](CharT ch){return std::isspace(ch);});
}

template<typename T>
static inline T strip(const T& s) {
    return strip<T, typename T::value_type>(s, [](typename T::value_type ch){return std::isspace(ch);});
}


// From list of char

template<typename T, typename CharT>
static inline void ilstrip(T& s, const char* list) {
    ilstrip<T, CharT>(s, [&list](CharT ch){
        return instring(ch, list);
    });
}

template<typename T>
static inline void ilstrip(T& s, const char* list) {
    ilstrip<T, typename T::value_type>(s, list);
}

template<typename T, typename CharT>
static inline void irstrip(T& s, const char* list) {
    irstrip<T, CharT>(s, [&list](CharT ch){
        return instring(ch, list);
    });
}

template<typename T>
static inline void irstrip(T& s, const char* list) {
    irstrip<T, typename T::value_type>(s, list);
}

template<typename T, typename CharT>
static inline void istrip(T& s, const char* list) {
    istrip<T, CharT>(s, [&list](CharT ch){
        return instring(ch, list);
    });
}

template<typename T>
static inline void istrip(T& s, const char* list) {
    istrip<T, typename T::value_type>(s, list);
}

/*
template<typename T, typename StringType, typename std::enable_if<is_basic_string<StringType>::value>::type = true>
static inline void ilstrip(T& s, const StringType& list) {
    ilstrip<T>(s, [&list](typename T::value_type ch){
        return instring(ch, list);
    });
}

template<typename T, typename StringType, typename std::enable_if<is_basic_string<StringType>::value>::type = true>
static inline void irstrip(T& s, const StringType& list) {
    irstrip<T>(s, [&list](typename T::value_type ch){
        return instring(ch, list);
    });
}

template<typename T, typename StringType, typename std::enable_if<is_basic_string<StringType>::value>::type = true>
static inline void istrip(T& s, const StringType& list) {
    istrip<T>(s, [&list](typename T::value_type ch){
        return instring(ch, list);
    });
}*/

#endif // CPPTOOLS_STRING_STRIP