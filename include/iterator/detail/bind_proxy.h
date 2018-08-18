#include <iterator/detail/mpl.h>

namespace iterator::detail {

template<typename T>
class bind_proxy
{
public:
	bind_proxy(T* data, std::size_t index) : data(data), index(index)
	{}

	bind_proxy(const bind_proxy& other)
	{
		index = other.index;
		data = new T(*other.data);
		copy = true;
	}

	bind_proxy& operator=(const bind_proxy&) = delete;

	void set_next_data(T* data)
	{
		this->data = data;
		++index;
	}

	template<std::size_t I>
	decltype(auto) get()
	{
		if constexpr(mpl::has_get_v<T>)
		{
			static_assert(I < mpl::tuple_size_v<T>);
			if constexpr(I < mpl::calculate_gets_v<T>)
				return std::get<I>(*data);

			else return (index);
		}

		else
		{
			static_assert(I < 2);
			if constexpr(I == 0) return *data;
			if constexpr(I == 1) return (index);
		}
	}

	template<std::size_t I>
	decltype(auto) get() const
	{
		if constexpr(mpl::has_get_v<T>)
		{
			static_assert(I < mpl::tuple_size_v<T>);
			if constexpr(I < mpl::calculate_gets_v<T>)
				return std::get<I>(*data);

			else return (index);
		}

		else
		{
			static_assert(I < 2);
			if constexpr(I == 0) return *data;
			if constexpr(I == 1) return (index);
		}
	}

	~bind_proxy()
	{
		if(copy) delete data;
		copy = false;
	}

private:
	T* data;
	std::size_t index;
	bool copy = false;
};

}

namespace std
{
	template<typename T>
	struct tuple_size<::iterator::detail::bind_proxy<T>>
	{
		constexpr static size_t value = ::iterator::detail::mpl::tuple_size_v<T>;
	};

	template<size_t I, typename T>
	struct tuple_element<I, ::iterator::detail::bind_proxy<T>>
	{
		using type = ::iterator::detail::mpl::tuple_element_t<I, T>;
	};
}
