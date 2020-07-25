cmake_minimum_required(VERSION 3.5)

PROJECT(EXAMPLE_SHADER VERSION 0.0.1 DESCRIPTION "Window example")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(OpenGL_GL_PREFERENCE "GLVND")

set(SOURCE example/shader/main.cpp )

add_executable(example_shader ${SOURCE})

message("${CMAKE_CURRENT_SOURCE_DIR}/engine/include")

target_include_directories(example_shader PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(example_shader engine)
