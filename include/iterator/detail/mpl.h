#pragma once
#include <type_traits>
#include <tuple>

namespace iterator::detail::mpl {

template<typename T, typename Cond = std::void_t<>>
struct has_get : std::false_type
{};

template<typename T>
struct has_get<T, std::void_t<decltype(std::tuple_cat(std::declval<T&>()))>> : std::true_type
{};

template<typename T>
constexpr bool has_get_v = has_get<T>::value;



template<typename T, typename Cond = std::void_t<>>
struct number_of_gets
{
	constexpr static std::size_t value = 1;
};

template<typename T>
struct number_of_gets<T, std::enable_if_t<has_get_v<T>>>
{
	constexpr static std::size_t value = std::tuple_size_v<T>;
};

template<typename T>
constexpr std::size_t number_of_gets_v = number_of_gets<T>::value;

template<typename T>
constexpr std::size_t indexed_iter_tuple_size_v = number_of_gets_v<T> + 1;



template<typename T, typename Cond = std::void_t<>>
struct hide_tuple_element
{
	template<std::size_t I>
	using type = T;
};

template<typename T>
struct hide_tuple_element<T, std::enable_if_t<has_get_v<T>>>
{
	template<std::size_t I>
	using type = std::tuple_element_t<I, T>;
};

struct indexed_iter_tuple_element
{
	template<std::size_t I, typename T>
	static auto check_get(T obj) -> std::enable_if_t<I <  number_of_gets_v<T>, hide_tuple_element<T>>;

	template<std::size_t I, typename T>
	static auto check_get(T obj) -> std::enable_if_t<I == number_of_gets_v<T>, hide_tuple_element<const std::size_t>>;

	template<std::size_t I, typename T>
	using type = typename decltype(check_get<I>(std::declval<T&>()))::template type<I>;
};

template<std::size_t I, typename T>
using indexed_iter_tuple_element_t = typename indexed_iter_tuple_element::type<I, T>;

} // namespace iterator::detail::mpl
