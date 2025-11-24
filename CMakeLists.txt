cmake_minimum_required(VERSION 3.14)
project(Figures_template)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

file(GLOB HEADER_FILES include/*.hpp)
file(GLOB IMPL_FILES impl/*.ipp) 
file(GLOB SOURCE_FILES src/*.cpp)

add_executable(List
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${IMPL_FILES}
)

target_include_directories(List PRIVATE include impl)

add_executable(list_tests
    test/listTest.cpp
    test/main.cpp
    src/customAllocator.cpp
    ${HEADER_FILES}
    ${IMPL_FILES}
)

target_link_libraries(list_tests GTest::gtest GTest::gtest_main)
target_include_directories(list_tests PRIVATE include impl)

include(GoogleTest)
gtest_discover_tests(list_tests)