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
struct calculate_gets
{
	constexpr static std::size_t value = 1;
};

template<typename T>
struct calculate_gets<T, std::enable_if_t<has_get_v<T>, std::void_t<>>>
{
	constexpr static std::size_t value = std::tuple_size_v<T>;
};

template<typename T>
constexpr std::size_t calculate_gets_v = calculate_gets<T>::value;

template<typename T>
constexpr std::size_t tuple_size_v = calculate_gets_v<T> + 1;



template<typename T, typename Cond = std::void_t<>>
struct hide_get
{
	template<std::size_t I>
	using type = T;
};

template<typename T>
struct hide_get<T, std::enable_if_t<has_get_v<T>, std::void_t<>>>
{
	template<std::size_t I>
	using type = std::tuple_element_t<I, T>;
};

struct tuple_element
{
	template<std::size_t I, typename T>
	static auto check_get(T obj) -> std::enable_if_t<I <  calculate_gets_v<T>, hide_get<T>>;

	template<std::size_t I, typename T>
	static auto check_get(T obj) -> std::enable_if_t<I == calculate_gets_v<T>, hide_get<const std::size_t>>;

	template<std::size_t I, typename T>
	using type = typename decltype(check_get<I>(std::declval<T&>()))::template type<I>;
};

template<std::size_t I, typename T>
using tuple_element_t = typename tuple_element::type<I, T>;

}