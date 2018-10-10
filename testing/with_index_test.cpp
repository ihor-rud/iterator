#include <gtest/gtest.h>
#include <tools/macro_helper.h>
#include <iterator/with_index.h>

namespace iterator {

template <typename T>
class with_index_test : public testing::Test
{};

using tested_types = ::testing::Types<float, double, std::string>;
TYPED_TEST_CASE(with_index_test, tested_types);

TYPED_TEST(with_index_test, vector_with_single_elem)
{
	std::vector<TypeParam> container(1);

	for(auto& [elem, index] : with_index(container))
	{
		EXPECT_EQ(elem, container[index]);
		EXPECT_EQ(&elem, &container[index]);

		static_assert(std::is_same_v<TypeParam, decltype(elem)>);
		static_assert(std::is_same_v<const std::size_t, decltype(index)>);
	}

	for(const auto& [elem, index] : with_index(container))
	{
		EXPECT_EQ(elem, container[index]);
		EXPECT_EQ(&elem, &container[index]);

		static_assert(std::is_same_v<const TypeParam, decltype(elem)>);
		static_assert(std::is_same_v<const std::size_t, decltype(index)>);
	}

	for(auto&& [elem, index] : with_index(container))
	{
		EXPECT_EQ(elem, container[index]);
		EXPECT_EQ(&elem, &container[index]);

		static_assert(std::is_same_v<TypeParam, decltype(elem)>);
		static_assert(std::is_same_v<const std::size_t, decltype(index)>);
	}
}

// DEFINE_VECTOR_TEST(with_index_test, vector_with_tuple, 1);
// DEFINE_VECTOR_TEST(with_index_test, vector_with_tuple, 2);

// TYPED_TEST(with_index_test, normal_map)
// {
// 	std::map<TypeParam, TypeParam> container = {{{}, {}}};

// 	for(auto& [key, val, index] : with_index(container))
// 	{
// 		EXPECT_EQ(val, container[key]);
// 		EXPECT_EQ(&val, &container[key]);

// 		static_assert(std::is_same_v<const TypeParam, decltype(key)>);
// 		static_assert(std::is_same_v<TypeParam, decltype(val)>);
// 		static_assert(std::is_same_v<const std::size_t, decltype(index)>);
// 	}

// 	for(const auto& [key, val, index] : with_index(container))
// 	{
// 		EXPECT_EQ(val, container[key]);
// 		EXPECT_EQ(&val, &container[key]);

// 		static_assert(std::is_same_v<const TypeParam, decltype(key)>);
// 		static_assert(std::is_same_v<const TypeParam, decltype(val)>);
// 		static_assert(std::is_same_v<const std::size_t, decltype(index)>);
// 	}

// 	for(auto&& [key, val, index] : with_index(container))
// 	{
// 		EXPECT_EQ(val, container[key]);
// 		EXPECT_EQ(&val, &container[key]);

// 		static_assert(std::is_same_v<const TypeParam, decltype(key)>);
// 		static_assert(std::is_same_v<TypeParam, decltype(val)>);
// 		static_assert(std::is_same_v<const std::size_t, decltype(index)>);
// 	}
// }

} // namespace iterator
