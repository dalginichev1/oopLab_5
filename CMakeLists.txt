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