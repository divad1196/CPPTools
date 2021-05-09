#ifndef CPPTOOLS_TUPLE_H
#define CPPTOOLS_TUPLE_H

#include <tuple>

// Todo: subtuple for indexes (index sequence), from slice
// Conditional index sequence


// template<std::size_t... I>
// class extract {
//     public:
//         template<typename... T>
//         static auto from(const std::tuple<T...>& a)
//         {
//             return std::make_tuple(std::get<I>(a)...);
//         }

//         template<typename... T>
//         static auto from(const T&... args)
//         {
//             return from(std::make_tuple(args...));
//         }
// };

template<std::size_t... I, typename... T>
auto extract(const std::tuple<T...>& t, std::index_sequence<I...>) {
    return std::make_tuple(std::get<I>(t)...);
}

template<std::size_t... I, typename... T>
auto extract(const std::tuple<T...>& t) {
    return extract(t, std::index_sequence<I...>{});
}

template<std::size_t... I, typename... T>
auto slice(const std::tuple<T...>& t, std::index_sequence<I...>) {
    return std::tie(std::get<I>(t)...);
}

template<std::size_t... I, typename... T>
auto slice(const std::tuple<T...>& t) {
    return slice(t, std::index_sequence<I...>{});
}

template<typename... T, typename... Types>
std::tuple<Types..., T...> extends(const std::tuple<Types...>& t, const T&... values) {
    return tuple_cat(t, std::make_tuple(values...));
}


template <bool Cond, typename... T, typename... Types>
auto cond_extends(const std::tuple<Types...>& t, const T&... values) {
    if constexpr(Cond)
        return extends(t, values...);
    else
        return t;
}

template<std::size_t I, std::size_t... Indexes>
std::index_sequence<Indexes..., I> extends(std::index_sequence<Indexes...>) {
    return {};
}

template <bool Cond, std::size_t I, std::size_t... Indexes>
auto cond_extends(std::index_sequence<Indexes...> seq) {
    if constexpr(Cond)
        return extends<I>(seq);
    else
        return seq;
}

template <std::size_t... I, std::size_t... J>
std::index_sequence<I..., J...> concat(std::index_sequence<I...>, std::index_sequence<J...>) {
    return {};
}

template<size_t I, typename... T>
constexpr bool in_range() {
    return I < sizeof...(T);
}
template<size_t I, typename... T>
constexpr bool in_range(const std::tuple<T...>& t) {
    return I < sizeof...(T);
}

template<template<typename> typename Cond, size_t I, typename... T, size_t... Indexes>
constexpr auto cond_index_seq(const std::tuple<T...>& t, std::index_sequence<Indexes...> seq) {
    using tuple_type = typename std::remove_cv<typename std::remove_reference<decltype(t)>::type>::type;
    if constexpr (in_range<I>(t)) {
        constexpr bool predicate = Cond<std::tuple_element_t<I, tuple_type>>::value;
        auto tmp = cond_extends<predicate, I>(seq);
        return cond_index_seq<Cond, (I + 1)>(t, tmp);
    } else
        return seq;
}


template<template<typename> typename Cond, typename... T>
constexpr auto cond_index_seq(const std::tuple<T...>& t) {
    return cond_index_seq<Cond, 0>(t, std::index_sequence<>{});
}

template<template<typename> typename Cond, typename... T>
auto cond_extract(const std::tuple<T...>& t) {
    return extract(t, cond_index_seq<Cond>(t));
}

template<class TupType, std::size_t... I>
void print_tuple(const TupType& _tup, std::index_sequence<I...>)
{
    std::cout << "(";
    (..., (std::cout << (I == 0 ? "" : ", ") << std::get<I>(_tup)));
    std::cout << ")\n";
}

template<class... T>
void print_tuple(const std::tuple<T...>& _tup)
{
    print_tuple(_tup, std::make_index_sequence<sizeof...(T)>());
}



# endif // CPPTOOLS_TUPLE_H