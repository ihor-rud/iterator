#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>

#define TEXT(z, index, data) data

#define NAME_ELEMENT(z, index, _)               element ## index

#define EXPECT_COMPARISON(z, index, comp)       EXPECT_EQ(NAME_ELEMENT(_, index, _),  std::get<index>(data[loop_index])); \
                                                comp(&NAME_ELEMENT(_, index, _), &std::get<index>(data[loop_index]));

#define EXPECT_DIFERENT_ADRESS_REPEAT(n)        BOOST_PP_REPEAT(n, EXPECT_COMPARISON, EXPECT_NE)
#define EXPECT_SAME_ADRESS_REPEAT(n)            BOOST_PP_REPEAT(n, EXPECT_COMPARISON, EXPECT_EQ)

#define EXPECT_TYPE(z, index, type)             testing::StaticAssertTypeEq<type, decltype(NAME_ELEMENT(_, index, _))>();
#define EXPECT_TYPE_REPEAT(n, type)             BOOST_PP_REPEAT(n, EXPECT_TYPE, type)



#define FOR_LOOP_AUTO_CHECK(type, number) \
	for(type auto [BOOST_PP_ENUM(number, NAME_ELEMENT, _), loop_index] : iterator::with_index(data)) \
	{ \
		EXPECT_DIFERENT_ADRESS_REPEAT(number); \
		EXPECT_TYPE_REPEAT(number, type TypeParam); \
		testing::StaticAssertTypeEq<const std::size_t, decltype(loop_index)>(); \
	}

#define FOR_LOOP_AUTO_REF_CHECK(type, loop_type, number) \
	for(type loop_type [BOOST_PP_ENUM(number, NAME_ELEMENT, _), loop_index] : iterator::with_index(data)) \
	{ \
		EXPECT_SAME_ADRESS_REPEAT(number); \
		EXPECT_TYPE_REPEAT(number, type TypeParam); \
		testing::StaticAssertTypeEq<const std::size_t, decltype(loop_index)>(); \
	}


#define DEFINE_VECTOR_TEST(name, description, n) \
	TYPED_TEST(name, description ## _ ## n) \
	{ \
		std::vector<std::tuple<BOOST_PP_ENUM(n, TEXT, TypeParam)>> data(10); \
		FOR_LOOP_AUTO_CHECK(     , n); \
		FOR_LOOP_AUTO_CHECK(const, n); \
		FOR_LOOP_AUTO_REF_CHECK(     , auto& , n); \
		FOR_LOOP_AUTO_REF_CHECK(const, auto& , n); \
		FOR_LOOP_AUTO_REF_CHECK(     , auto&&, n); \
	}
