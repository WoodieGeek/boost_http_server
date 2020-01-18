cmake_minimum_required(VERSION 3.10)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost COMPONENTS chrono filesystem REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} library)

link_directories(library)

add_subdirectory(library)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -pthread")

add_executable(main main.cpp)

target_link_libraries(main ${Boost_LIBRARIES} library)
