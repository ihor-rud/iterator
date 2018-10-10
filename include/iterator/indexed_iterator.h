#pragma once
#include <iterator/recursive_unpack/recursive_unpack.h>

namespace iterator {

template<typename T,
    template<typename> typename unpack_policy = detail::recursive_unpack>
class indexed_iterator
{
public:
	indexed_iterator(T itr) : proxy(itr)
	{}

	bool operator!=(const indexed_iterator& other) const
	{
		return proxy != other.proxy;
	}

	indexed_iterator& operator++()
	{
		++proxy;
		return *this;
	}

	decltype(auto) operator*()
	{
		return (proxy);
	}

private:
	unpack_policy<T> proxy;
};

} // namespace iterator
