#pragma once
#include <tuple>
#include <type_traits>

namespace iterator::mpl {

template<typename T, typename = std::void_t<>>
struct is_tuple_like : std::false_type
{};

template<typename T>
struct is_tuple_like<T, std::void_t<decltype(std::tuple_cat(std::declval<T&>()))>> : std::true_type
{};

template<typename T>
constexpr bool is_tuple_like_v = is_tuple_like<T>::value;

} // namespace iterator::mpl
