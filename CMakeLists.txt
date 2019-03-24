cmake_minimum_required(VERSION 2.8)

project(jsonRPC)

add_executable(JsonRpc main.cpp JsonRpc.cpp)

target_link_libraries(JsonRpc json)
