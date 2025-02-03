cmake_minimum_required(VERSION 3.10)

# Define project name and set language
project(my_executable LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG -g -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# Define the executable target
add_executable(${PROJECT_NAME} driver.cpp)
