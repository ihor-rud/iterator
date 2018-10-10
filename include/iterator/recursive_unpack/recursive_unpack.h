#pragma once
#include <iterator/recursive_unpack/mpl.h>

namespace iterator::detail {

template<typename T>
class recursive_unpack
{
public:
	using data_type = typename std::iterator_traits<T>::value_type;

	recursive_unpack(T data) : data(data)
	{}

	recursive_unpack(const recursive_unpack&) = delete;
	recursive_unpack& operator=(const recursive_unpack&) = delete;

	recursive_unpack& operator++()
	{
		++data;
		++index;
		return *this;
	}

	bool operator!=(const recursive_unpack& other) const
	{
		return data != other.data;;
	}

	template<std::size_t I>
	decltype(auto) get() const
	{
		static_assert(I < mpl::indexed_iter_tuple_size_v<data_type>);

		if constexpr(mpl::has_get_v<data_type>)
		{
			if constexpr(I < mpl::number_of_gets_v<data_type>)
				return std::get<I>(*data);

			else return index;
		}

		else
		{
			if constexpr(I == 0) return *data;
			if constexpr(I == 1) return index;
		}
	}

private:
	T data;
	std::size_t index = 0;
};

} // namespace iterator::detail

namespace std {

template<typename T>
struct tuple_size<::iterator::detail::recursive_unpack<T>>
{
	constexpr static size_t value =
	    ::iterator::detail::mpl::indexed_iter_tuple_size_v<typename std::iterator_traits<T>::value_type>;
};

template<size_t I, typename T>
struct tuple_element<I, ::iterator::detail::recursive_unpack<T>>
{
	using type =
	    ::iterator::detail::mpl::indexed_iter_tuple_element_t<I, typename std::iterator_traits<T>::value_type>;
};

} // namespace std
