cmake_minimum_required(VERSION 3.10)
project(i2c_interface CXX)

set(CMAKE_CXX_STANDARD 17)

add_library(i2c-interface i2c-interface/i2c-intf.hpp)
set_target_properties(i2c-interface PROPERTIES LINKER_LANGUAGE CXX)

add_library(i2c-linux adapters/i2c-linux-adapter.cpp)
target_include_directories(i2c-linux PUBLIC i2c-interface)

add_executable(i2c-interface-test main.cpp)
target_include_directories(i2c-interface-test PUBLIC adapters i2c-interface)
target_link_libraries(i2c-interface-test i2c-linux)
