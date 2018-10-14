#pragma once
#include <tuple>
#include <type_traits>

namespace iterator::detail::mpl {

template<typename T, typename = std::void_t<>>
struct is_tuple_like : std::false_type
{};

template<typename T>
struct is_tuple_like<T, std::void_t<decltype(std::tuple_cat(std::declval<T&>()))>> : std::true_type
{};

template<typename T>
constexpr bool is_tuple_like_v = is_tuple_like<T>::value;



template<typename T, std::size_t Deep, bool recursive = is_tuple_like_v<T>>
struct recursive_tuple_size_impl
{
	template<std::size_t... Seq>
	constexpr static std::size_t get_recursive_tuple_size(std::index_sequence<Seq...>)
	{
		return (recursive_tuple_size_impl<std::tuple_element_t<Seq, T>, Deep - 1, is_tuple_like_v<std::tuple_element_t<Seq, T>>>::value + ...);
	}

	constexpr static std::size_t value = get_recursive_tuple_size(std::make_index_sequence<std::tuple_size_v<T>>{});
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





template<std::size_t Idx, typename T, std::size_t Deep>
struct recursive_tuple_element
{
	static_assert(Idx < recursive_tuple_size_v<T, Deep>);
	using type = void;
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

} // namespace iterator::detail::mpl
