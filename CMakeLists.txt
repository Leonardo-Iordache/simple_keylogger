cmake_minimum_required(VERSION 3.28)
project(kylogger)

set(CMAKE_CXX_STANDARD 20)

add_executable(kylogger main.cpp)

find_package(CURL REQUIRED)
target_link_libraries(kylogger PRIVATE CURL::libcurl)