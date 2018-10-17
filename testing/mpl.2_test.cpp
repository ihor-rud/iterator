#include <iterator/recursive_unpack/mpl.2.h>

namespace iterator::mpl {

// ----------------------------------------------------------------
//                   recursive_tuple_size
// ----------------------------------------------------------------
static_assert(recursive_tuple_size_v<std::tuple<int, std::tuple<float, double>>, 0> == 1);
static_assert(recursive_tuple_size_v<std::tuple<int, std::tuple<float, double>>, 1> == 2);
static_assert(recursive_tuple_size_v<std::tuple<int, std::tuple<float, double>>, 2> == 3);
static_assert(recursive_tuple_size_v<std::tuple<int, std::tuple<float, double>>, 3> == 3);

// ----------------------------------------------------------------
//                   recursive_tuple_element
// ----------------------------------------------------------------
static_assert(std::is_same_v<recursive_tuple_element_t<0, std::tuple<int, std::tuple<float, double>>, 0>, std::tuple<int, std::tuple<float, double>>>);

static_assert(std::is_same_v<recursive_tuple_element_t<0, std::tuple<int, std::tuple<float, double>>, 1>, int>);
static_assert(std::is_same_v<recursive_tuple_element_t<1, std::tuple<int, std::tuple<float, double>>, 1>, std::tuple<float, double>>);

static_assert(std::is_same_v<recursive_tuple_element_t<0, std::tuple<int, std::tuple<float, double>>, 2>, int>);
static_assert(std::is_same_v<recursive_tuple_element_t<1, std::tuple<int, std::tuple<float, double>>, 2>, float>);
static_assert(std::is_same_v<recursive_tuple_element_t<2, std::tuple<int, std::tuple<float, double>>, 2>, double>);

} // namespace iterator::detail::mpl
