cmake_minimum_required(VERSION 3.10)
project(iterator)

set(CMAKE_CXX_STANDARD 17)
set(DEFAULT_IMPORT_DIR "/home/ihor/Downloads")

add_library(ITERATOR INTERFACE)
set_target_properties(ITERATOR PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/include")

add_library(BOOST_INTERFACE INTERFACE)
set_target_properties(BOOST_INTERFACE PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${DEFAULT_IMPORT_DIR}/boost_1_68_0")

add_library(GTEST STATIC IMPORTED)
set_target_properties(GTEST PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${DEFAULT_IMPORT_DIR}/googletest/googletest/include")
set_target_properties(GTEST PROPERTIES IMPORTED_LOCATION "${DEFAULT_IMPORT_DIR}/googletest/googlemock/gtest/libgtest.a")

add_library(GTEST_MAIN STATIC IMPORTED)
set_target_properties(GTEST_MAIN PROPERTIES IMPORTED_LOCATION "${DEFAULT_IMPORT_DIR}/googletest/googlemock/gtest/libgtest_main.a")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(tests testing/with_index_test.cpp)
target_include_directories(tests PRIVATE "${CMAKE_SOURCE_DIR}/testing")
target_link_libraries(tests ITERATOR GTEST GTEST_MAIN BOOST_INTERFACE Threads::Threads)
target_compile_options(tests PRIVATE -Wall -Wextra -Wfatal-errors)
