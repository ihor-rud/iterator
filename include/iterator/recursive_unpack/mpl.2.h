#pragma once
#include <iterator/mpl/tools.h>

namespace iterator::mpl {

template<typename T, std::size_t Deep, bool recursive = is_tuple_like_v<T>>
struct recursive_tuple_size_impl
{
	template<std::size_t... Seq>
	constexpr static std::size_t sum_recursive_tuple_sizes(std::index_sequence<Seq...>)
	{
		return (recursive_tuple_size_impl<std::tuple_element_t<Seq, T>, Deep - 1>::value + ...);
	}

	constexpr static std::size_t value = sum_recursive_tuple_sizes(std::make_index_sequence<std::tuple_size_v<T>>{});
};

template<typename T, std::size_t Deep>
struct recursive_tuple_size_impl<T, Deep, false>
{
	constexpr static std::size_t value = 1;
};

template<typename T>
struct recursive_tuple_size_impl<T, 0, true>
{
	constexpr static std::size_t value = 1;
};

template<typename T, std::size_t Deep>
struct recursive_tuple_size
{
	constexpr static std::size_t value = recursive_tuple_size_impl<T, Deep>::value;
};

template<typename T, std::size_t Deep>
constexpr std::size_t recursive_tuple_size_v = recursive_tuple_size<T, Deep>::value;



template<std::size_t Idx, typename T, std::size_t Deep, bool recursive = is_tuple_like_v<T>>
struct recursive_tuple_element_impl;

template<std::size_t Offset, std::size_t Deep, typename...>
struct recursive_tuple_element_helper;

template<std::size_t Offset, std::size_t Deep, typename Head, typename... Tail>
struct recursive_tuple_element_helper<Offset, Deep, Head, Tail...>
{
	constexpr static std::size_t head_length = recursive_tuple_size_v<Head, Deep>;
	using type = typename std::conditional_t<
	    Offset < head_length,
	        recursive_tuple_element_impl<Offset, Head, Deep - 1>,
	        recursive_tuple_element_helper<Offset - head_length, Deep, Tail...>>::type;
};

template<std::size_t Idx, typename T, std::size_t Deep, bool recursive>
struct recursive_tuple_element_impl
{
	template<std::size_t... Seq>
	constexpr static auto get_recursive_tuple_size(std::index_sequence<Seq...>)
	    -> typename recursive_tuple_element_helper<Idx, Deep, std::tuple_element_t<Seq, T>...>::type;

	using type = decltype(get_recursive_tuple_size(std::make_index_sequence<std::tuple_size_v<T>>{}));
};

template<typename T, std::size_t Deep>
struct recursive_tuple_element_impl<0, T, Deep, false>
{
	using type = T;
};

template<typename T>
struct recursive_tuple_element_impl<0, T, 0, true>
{
	using type = T;
};

template<std::size_t Idx, typename T, std::size_t Deep>
struct recursive_tuple_element
{
	static_assert(Idx < recursive_tuple_size_v<T, Deep>);
	using type = typename recursive_tuple_element_impl<Idx, T, Deep>::type;
};

template<std::size_t Idx, typename T, std::size_t Deep>
using recursive_tuple_element_t = typename recursive_tuple_element<Idx, T, Deep>::type;



template<typename T, typename Cond = std::void_t<>>
struct hide_tuple_element
{
	template<std::size_t Idx>
	using type = T;
};

template<typename T>
struct hide_tuple_element<T, std::enable_if_t<is_tuple_like_v<T>>>
{
	template<std::size_t Idx>
	using type = std::tuple_element_t<Idx, T>;
};

// struct indexed_iter_tuple_element
// {
// 	template<std::size_t Idx, typename T>
// 	static auto check_get(T obj) -> std::enable_if_t<Idx <  number_of_gets_v<T>, hide_tuple_element<T>>;

// 	template<std::size_t Idx, typename T>
// 	static auto check_get(T obj) -> std::enable_if_t<Idx == number_of_gets_v<T>, hide_tuple_element<const std::size_t>>;

// 	template<std::size_t Idx, typename T>
// 	using type = typename decltype(check_get<Idx>(std::declval<T&>()))::template type<Idx>;
// };

// template<std::size_t Idx, typename T>
// using recursive_unpack_tuple_element_t = typename indexed_iter_tuple_element::type<Idx, T>;

} // namespace iterator::mpl
