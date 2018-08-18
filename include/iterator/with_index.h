#include <iterator/detail/indexed_iterator.h>

namespace iterator {

template<typename T>
class with_index
{
public:
	with_index(T& obj) : obj(obj)
	{}

	auto begin()
	{
		return detail::indexed_iterator{std::begin(obj)};
	}

	auto end()
	{
		return detail::indexed_iterator{std::end(obj)};
	}

private:
	T& obj;
};

}