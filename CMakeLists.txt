cmake_minimum_required(VERSION 3.1)
project(tinkerforge-example CXX)

find_package(fmt REQUIRED CONFIG)
find_package(CLI11 REQUIRED CONFIG)
find_package(tinkerforge-bindings REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} poti_callback.cpp)
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 11)
target_link_libraries(${CMAKE_PROJECT_NAME} CLI11::CLI11 fmt::fmt tinkerforge::bindings)
