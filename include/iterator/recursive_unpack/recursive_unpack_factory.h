#pragma once
#include "recursive_unpack.h"

namespace iterator::detail {

template<std::size_t N>
struct recursive_unpack_factory
{
	template<typename Iter>
	using type = recursive_unpack<Iter, N>;
};

}
