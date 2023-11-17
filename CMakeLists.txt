cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 11)

project(OpenGLRenderer)

add_executable(game main.cpp glad.c util/stb_image.cpp include/Perlin.cpp lib/imgui/imgui.cpp lib/imgui/imgui_draw.cpp lib/imgui/imgui_tables.cpp lib/imgui/imgui_widgets.cpp  lib/imgui/backends/imgui_impl_opengl3.cpp lib/imgui/backends/imgui_impl_glfw.cpp)

add_subdirectory(lib/glfw)

target_link_libraries(game PUBLIC glfw)
target_include_directories(game PRIVATE include)
target_include_directories(game PRIVATE lib/glm)
target_include_directories(game PRIVATE lib/imgui lib/imgui/backends)

