cmake_minimum_required(VERSION 3.15)

project(OpenGLRenderer)

add_executable(game main.cpp glad.c util/stb_image.cpp)

add_subdirectory(lib/glfw)

target_link_libraries(game PUBLIC glfw)
target_include_directories(game PRIVATE include)
target_include_directories(game PRIVATE lib/glm)

