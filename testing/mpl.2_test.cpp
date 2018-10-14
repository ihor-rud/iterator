#include <iterator/recursive_unpack/mpl.2.h>

static_assert(iterator::detail::mpl::recursive_tuple_size_v<std::tuple<int>, 0> == 1);
static_assert(iterator::detail::mpl::recursive_tuple_size_v<std::tuple<int>, 1> == 1);
static_assert(iterator::detail::mpl::recursive_tuple_size_v<std::tuple<int>, 2> == 1);

static_assert(iterator::detail::mpl::recursive_tuple_size_v<std::tuple<int, int>, 0> == 1);
static_assert(iterator::detail::mpl::recursive_tuple_size_v<std::tuple<int, int>, 1> == 2);
static_assert(iterator::detail::mpl::recursive_tuple_size_v<std::tuple<int, int>, 2> == 2);

static_assert(iterator::detail::mpl::recursive_tuple_size_v<std::tuple<std::tuple<int, int>>, 0> == 1);
static_assert(iterator::detail::mpl::recursive_tuple_size_v<std::tuple<std::tuple<int, int>>, 1> == 1);
static_assert(iterator::detail::mpl::recursive_tuple_size_v<std::tuple<std::tuple<int, int>>, 2> == 2);

static_assert(iterator::detail::mpl::recursive_tuple_size_v<std::tuple<std::tuple<int, int>, std::tuple<int, int>>, 0> == 1);
static_assert(iterator::detail::mpl::recursive_tuple_size_v<std::tuple<std::tuple<int, int>, std::tuple<int, int>>, 1> == 2);
static_assert(iterator::detail::mpl::recursive_tuple_size_v<std::tuple<std::tuple<int, int>, std::tuple<int, int>>, 2> == 4);

static_assert(iterator::detail::mpl::recursive_tuple_size_v<std::tuple<int, std::tuple<int, int>>, 0> == 1);
static_assert(iterator::detail::mpl::recursive_tuple_size_v<std::tuple<int, std::tuple<int, int>>, 1> == 2);
static_assert(iterator::detail::mpl::recursive_tuple_size_v<std::tuple<int, std::tuple<int, int>>, 2> == 3);
