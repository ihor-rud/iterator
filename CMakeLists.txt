cmake_minimum_required(VERSION 3.11)
project(iterator)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

add_library(ITERATOR INTERFACE)
set_target_properties(ITERATOR PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/include")

set(DEFAULT_IMPORT_DIR "/home/ihor/Downloads")
add_library(BOOST_INTERFACE INTERFACE)
set_target_properties(BOOST_INTERFACE PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${DEFAULT_IMPORT_DIR}/boost_1_67_0")

add_executable(test test/with_index_test.cpp)
target_include_directories(test PRIVATE "${CMAKE_SOURCE_DIR}/test")
target_link_libraries(test ITERATOR GTest::GTest GTest::Main BOOST_INTERFACE)
target_compile_options(test PRIVATE -Wall -Wextra)
