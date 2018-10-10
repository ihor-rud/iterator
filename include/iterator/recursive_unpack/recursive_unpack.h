#pragma once
#include "mpl.h"

namespace iterator::detail {

template<typename Iter, std::size_t N>
class recursive_unpack;

template<typename Iter>
class recursive_unpack<Iter, 0>
{
public:
	using data_type = typename std::iterator_traits<Iter>::value_type;

	recursive_unpack(Iter iter) : iter(iter)
	{}

	recursive_unpack(const recursive_unpack&) = delete;
	recursive_unpack& operator=(const recursive_unpack&) = delete;

	recursive_unpack& operator++()
	{
		++iter;
		++index;
		return *this;
	}

	bool operator!=(const recursive_unpack& other) const
	{
		return iter != other.iter;;
	}

	template<std::size_t Idx>
	decltype(auto) get() const
	{
		if constexpr(Idx == 0) return *iter;
		if constexpr(Idx == 1) return index;
	}

protected:
	Iter iter;
	std::size_t index = 0;
};

template<typename Iter, std::size_t N>
class recursive_unpack : public recursive_unpack<Iter, 0>
{
public:
	using recursive_unpack<Iter, 0>::recursive_unpack;
	using typename recursive_unpack<Iter, 0>::data_type;

	template<std::size_t Idx>
	decltype(auto) get() const
	{
		static_assert(Idx < mpl::recursive_unpack_tuple_size_v<data_type>);

		if constexpr(N && mpl::has_get_v<data_type>)
		{
			if constexpr(Idx < mpl::number_of_gets_v<data_type>)
				return std::get<Idx>(*this->iter);
		}

		return recursive_unpack<Iter, 0>::template get<Idx>();
	}
};

} // namespace iterator::detail

namespace std {

template<typename Iter>
struct tuple_size<::iterator::detail::recursive_unpack<Iter, 1>>
{
	constexpr static size_t value =
	    ::iterator::detail::mpl::recursive_unpack_tuple_size_v<typename std::iterator_traits<Iter>::value_type>;
};

template<size_t Idx, typename Iter>
struct tuple_element<Idx, ::iterator::detail::recursive_unpack<Iter, 1>>
{
	using type =
	    ::iterator::detail::mpl::recursive_unpack_tuple_element_t<Idx, typename std::iterator_traits<Iter>::value_type>;
};

} // namespace std
