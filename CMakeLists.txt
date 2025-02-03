cmake_minimum_required(VERSION 3.10)
project(my_executable)

set(CMAKE_CXX_STANDARD 17)

# Set C++ compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG -g -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Add executable target
add_executable(${PROJECT_NAME} driver.cpp)
