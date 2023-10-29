#include "Shaders.hpp"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

unsigned int LoadShaders(const char *vertex_file_path,
                         const char *fragment_file_path) {
  std::cout << "Loading Shaders...";

  unsigned int VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
  unsigned int FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

  std::string VertexShaderCode;
  std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
  if (VertexShaderStream.is_open()) {
    std::string Line = "";
    while (getline(VertexShaderStream, Line))
      VertexShaderCode += "\n" + Line;
    VertexShaderStream.close();
  }

  std::cout << VertexShaderCode;
}
