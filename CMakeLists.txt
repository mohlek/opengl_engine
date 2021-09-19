cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

project(engine VERSION 0.0.1 DESCRIPTION "Simple engine")
file(GLOB_RECURSE src_engine "src/*.cpp")

add_subdirectory(extern/)

#########################################################
# FIND SDL
#########################################################
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

#########################################################
# FIND ASSIMP
#########################################################
find_package(ASSIMP REQUIRED)
include_directories(${ASSIMP_INCLUDE_DIRS})


if (EXAMPLES)
  include("example/window/CMakeLists.txt")
  include("example/shader/CMakeLists.txt")
endif (EXAMPLES)


add_library(engine STATIC ${src_engine})

target_include_directories(engine PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(engine PUBLIC ${ASSIMP_LIBRARIES})
target_link_libraries(engine PUBLIC SDL2::SDL2)
target_link_libraries(engine PUBLIC gl3w)
target_link_libraries(engine PUBLIC imgui)
