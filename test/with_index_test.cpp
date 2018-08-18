#include <gtest/gtest.h>
#include <tools/macro_helper.h>
#include <iterator/with_index.h>

template <typename T>
class with_index_test : public testing::Test
{};

using MyTypes = ::testing::Types<float, double, std::string>;
TYPED_TEST_CASE(with_index_test, MyTypes);

TYPED_TEST(with_index_test, test_vector_with_single_elem)
{
	std::vector<TypeParam> data(10);

	for(auto [elem, index] : iterator::with_index(data))
	{
		EXPECT_EQ(elem, data[index]);
		EXPECT_NE(&elem, &data[index]);
		testing::StaticAssertTypeEq<TypeParam, decltype(elem)>();
		testing::StaticAssertTypeEq<const std::size_t, decltype(index)>();
	}

	for(const auto [elem, index] : iterator::with_index(data))
	{
		EXPECT_EQ(elem, data[index]);
		EXPECT_NE(&elem, &data[index]);
		testing::StaticAssertTypeEq<const TypeParam, decltype(elem)>();
		testing::StaticAssertTypeEq<const std::size_t, decltype(index)>();
	}

	for(auto& [elem, index] : iterator::with_index(data))
	{
		EXPECT_EQ(elem, data[index]);
		EXPECT_EQ(&elem, &data[index]);
		testing::StaticAssertTypeEq<TypeParam, decltype(elem)>();
		testing::StaticAssertTypeEq<const std::size_t, decltype(index)>();
	}

	for(const auto& [elem, index] : iterator::with_index(data))
	{
		EXPECT_EQ(elem, data[index]);
		EXPECT_EQ(&elem, &data[index]);
		testing::StaticAssertTypeEq<const TypeParam, decltype(elem)>();
		testing::StaticAssertTypeEq<const std::size_t, decltype(index)>();
	}

	for(auto&& [elem, index] : iterator::with_index(data))
	{
		EXPECT_EQ(elem, data[index]);
		EXPECT_EQ(&elem, &data[index]);
		testing::StaticAssertTypeEq<TypeParam, decltype(elem)>();
		testing::StaticAssertTypeEq<const std::size_t, decltype(index)>();
	}
}

DEFINE_VECTOR_TEST(with_index_test, test_vector_with_tuple, 1);
DEFINE_VECTOR_TEST(with_index_test, test_vector_with_tuple, 2);
DEFINE_VECTOR_TEST(with_index_test, test_vector_with_tuple, 3);
DEFINE_VECTOR_TEST(with_index_test, test_vector_with_tuple, 4);
DEFINE_VECTOR_TEST(with_index_test, test_vector_with_tuple, 5);
DEFINE_VECTOR_TEST(with_index_test, test_vector_with_tuple, 6);

TYPED_TEST(with_index_test, test_map)
{
	std::map<TypeParam, TypeParam> data;

	for(auto [key, data, index] : iterator::with_index(data))
	{
		testing::StaticAssertTypeEq<const TypeParam, decltype(key)>();
		testing::StaticAssertTypeEq<TypeParam, decltype(data)>();
		testing::StaticAssertTypeEq<const std::size_t, decltype(index)>();
	}

	for(const auto [key, data, index] : iterator::with_index(data))
	{
		testing::StaticAssertTypeEq<const TypeParam, decltype(key)>();
		testing::StaticAssertTypeEq<const TypeParam, decltype(data)>();
		testing::StaticAssertTypeEq<const std::size_t, decltype(index)>();
	}

	for(auto& [key, data, index] : iterator::with_index(data))
	{
		testing::StaticAssertTypeEq<const TypeParam, decltype(key)>();
		testing::StaticAssertTypeEq<TypeParam, decltype(data)>();
		testing::StaticAssertTypeEq<const std::size_t, decltype(index)>();
	}

	for(const auto& [key, data, index] : iterator::with_index(data))
	{
		testing::StaticAssertTypeEq<const TypeParam, decltype(key)>();
		testing::StaticAssertTypeEq<const TypeParam, decltype(data)>();
		testing::StaticAssertTypeEq<const std::size_t, decltype(index)>();
	}

	for(auto&& [key, data, index] : iterator::with_index(data))
	{
		testing::StaticAssertTypeEq<const TypeParam, decltype(key)>();
		testing::StaticAssertTypeEq<TypeParam, decltype(data)>();
		testing::StaticAssertTypeEq<const std::size_t, decltype(index)>();
	}
}
