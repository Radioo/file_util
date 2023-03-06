cmake_minimum_required(VERSION 3.24)
project(file_util)

set(CMAKE_CXX_STANDARD 23)
set(BOOST_INCLUDE_LIBRARIES algorithm)
set(BOOST_ENABLE_CMAKE ON)

include(FetchContent)
FetchContent_Declare(
        boost
        GIT_REPOSITORY https://github.com/boostorg/boost.git
)
FetchContent_MakeAvailable(boost)

add_executable(file_util main.cpp)
target_link_libraries(file_util PRIVATE Boost::algorithm)
