cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(engine VERSION 0.0.1 DESCRIPTION "Simple engine")

file(GLOB_RECURSE src_engine "src/*.cpp")

#########################################################
# FIND OpenGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
link_directories(${OPENGL_LIBRARY_DIRS})
add_definitions(${OPENGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OpenGL not found!")
endif(NOT OPENGL_FOUND)

#########################################################
# FIND GLEW
#########################################################
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARY_DIRS})
add_definitions(${GLEW_DEFINITIONS})
if(NOT GLEW_FOUND)
    message(ERROR " GLEW not found!")
endif(NOT GLEW_FOUND)

#########################################################
# FIND SDL
#########################################################
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

#########################################################
# FIND GLFW
#########################################################
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
#find_package(glfw3 REQUIRED)

include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})
add_definitions(${GLDFW_DEFINITIONS})
if(NOT GLFW_FOUND)
    message(ERROR " GLFW not found!")
endif(NOT GLFW_FOUND)

#########################################################
# FIND GLM
#########################################################
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

if(NOT GLM_FOUND)
    message(Error " GLM not found")
endif(NOT GLM_FOUND)

add_library(engine STATIC ${src_engine})

target_include_directories(engine INTERFACE "${GLM_INCLUDE_DIRS}")
target_link_libraries(engine INTERFACE ${OPENGL_LIBRARIES}) 
target_link_libraries(engine INTERFACE ${GLEW_LIBRARIES})
target_link_libraries(engine INTERFACE ${SDL2_LIBRARIES})
target_link_libraries(engine INTERFACE ${LIB3DS_LIBRARY})
