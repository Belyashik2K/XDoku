cmake_minimum_required(VERSION 3.30)
project(XDoku)

set(CMAKE_CXX_STANDARD 26)

find_package(PostgreSQL REQUIRED)
find_package(libpqxx REQUIRED)

add_executable(XDoku main.cpp)

target_link_libraries(XDoku PRIVATE pqxx pq)
