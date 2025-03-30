cmake_minimum_required(VERSION 3.30)
project(XDoku)

set(CMAKE_CXX_STANDARD 26)

find_package(PostgreSQL REQUIRED)
find_package(libpqxx REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(XDoku
        main.cpp
        deps/glad/src/glad.c
)

target_include_directories(XDoku PRIVATE
        ${PROJECT_SOURCE_DIR}/deps/glad/include
)

target_link_libraries(XDoku PRIVATE
        pqxx
        pq
        glfw
        OpenGL::GL
        pthread
)
