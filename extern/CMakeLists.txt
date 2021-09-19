include(FindPkgConfig)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(gl3w)

# IMGUI STUFF
project(imgui)
add_library(imgui STATIC
  imgui/imgui.cpp
  imgui/imgui_widgets.cpp
  imgui/imgui_tables.cpp
  imgui/imgui_draw.cpp
  imgui/backends/imgui_impl_sdl.cpp 
  imgui/backends/imgui_impl_opengl3.cpp
)
target_compile_definitions(imgui PUBLIC IMGUI_DISABLE_DEMO_WINDOWS)
target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_GL3W)
target_include_directories(imgui PUBLIC "imgui" "imgui/backends")
target_link_libraries(imgui PUBLIC SDL2::SDL2 OpenGL gl3w)
