cmake_minimum_required(VERSION 2.8)

project(jsonRPC)

add_executable(JsonRpc main.cpp JsonRpc.cpp client.cpp)

set(CMAKE_CXX_FLAGS -g)

target_link_libraries(JsonRpc json)
target_link_libraries(JsonRpc curl)
