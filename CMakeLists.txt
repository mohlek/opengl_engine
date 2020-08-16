cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

project(engine VERSION 0.0.1 DESCRIPTION "Simple engine")

add_subdirectory(framework/)

file(GLOB_RECURSE src_engine "src/*.cpp")

#########################################################
# FIND SDL
#########################################################
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


if (EXAMPLES)
  include("example/window/CMakeLists.txt")
  include("example/shader/CMakeLists.txt")
endif (EXAMPLES)

add_library(engine STATIC ${src_engine})

target_include_directories(engine INTERFACE "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(engine INTERFACE SDL2::SDL2)
target_link_libraries(engine PUBLIC framework)
