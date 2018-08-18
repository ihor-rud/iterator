#include "bind_proxy.h"

namespace iterator::detail {

template<typename T>
class indexed_iterator
{
public:
	indexed_iterator(T itr) : itr(itr), proxy(&*itr, 0)
	{}

	bool operator!=(const indexed_iterator& other) const
	{
		return itr != other.itr;
	}

	indexed_iterator& operator++()
	{
		++itr;
		proxy.set_next_data(&*itr);
		return *this;
	}

	decltype(auto) operator*()
	{
		return (proxy);
	}

private:
	T itr;
	bind_proxy<typename T::value_type> proxy;
};

}