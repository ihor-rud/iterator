#pragma once
#include "indexed_iterator.h"

namespace iterator {

template<typename T>
class with_index
{
public:
	with_index(T& obj) : obj(obj)
	{}

	auto begin()
	{
		using std::begin;
		return indexed_iterator{begin(obj)};
	}

	auto end()
	{
		using std::end;
		return indexed_iterator{end(obj)};
	}

private:
	T& obj;
};

} // namespace iterator
