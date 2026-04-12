cmake_minimum_required(VERSION 3.20)
project(MathServiceApp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")
include_directories(include)
include_directories(include /opt/homebrew/include /usr/local/include /usr/include)
add_executable(math_app ${SOURCES})
target_link_libraries(math_app pqxx pq pthread)