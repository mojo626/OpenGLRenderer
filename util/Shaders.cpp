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
  std::cout << "Loading Shaders...\n";

  unsigned int VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
  unsigned int FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

  // read vertex shader code from file
  std::string VertexShaderCode;
  std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
  if (VertexShaderStream.is_open()) {
    std::string Line = "";
    while (getline(VertexShaderStream, Line))
      VertexShaderCode += "\n" + Line;
    VertexShaderStream.close();
  }

  // read fragment shader code from file
  std::string FragmentShaderCode;
  std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
  if (FragmentShaderStream.is_open()) {
    std::string Line = "";
    while (getline(FragmentShaderStream, Line))
      FragmentShaderCode += "\n" + Line;
    FragmentShaderStream.close();
  }

  int success;
  char infoLog[512];

  std::cout << "compiling shader " << vertex_file_path << "\n";
  // convert string to c string
  char const *VertexSourcePointer = VertexShaderCode.c_str();
  glShaderSource(VertexShaderId, 1, &VertexSourcePointer, NULL);
  glCompileShader(VertexShaderId);

  glGetShaderiv(VertexShaderId, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(VertexShaderId, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  std::cout << "compiling shader " << fragment_file_path << std::endl;
  char const *FragmentSourcePointer = FragmentShaderCode.c_str();
  glShaderSource(FragmentShaderId, 1, &FragmentSourcePointer, NULL);
  glCompileShader(FragmentShaderId);

  glGetShaderiv(FragmentShaderId, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(FragmentShaderId, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  std::cout << "linking program..." << std::endl;
  unsigned int ShaderProgram;
  ShaderProgram = glCreateProgram();

  glAttachShader(ShaderProgram, VertexShaderId);
  glAttachShader(ShaderProgram, FragmentShaderId);
  glLinkProgram(ShaderProgram);

  glDeleteShader(VertexShaderId);
  glDeleteShader(FragmentShaderId);

  return ShaderProgram;
}
