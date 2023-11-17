#include <cstdlib>
#define GLFW_INCLUDE_NONE
#include "util/Camera.h"
#include "util/Cube.hpp"
#include "util/Shaders.hpp"
#include "util/stb_image.h"
#include <GLFW/glfw3.h>
#include <Perlin.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "util/Chunk.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

bool wireframe = false;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float lastX = 400, lastY = 300;
Camera cam(glm::vec3(0.0f, 0.0f, 3.0f));

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window, Camera *cam) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  if (glfwGetKey(window, GLFW_KEY_APOSTROPHE) == GLFW_PRESS)
    wireframe = !wireframe;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    cam->HandleInput(FORWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    cam->HandleInput(BACKWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    cam->HandleInput(LEFT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    cam->HandleInput(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {

  float xoffset = xpos - lastX;
  float yoffset =
      lastY - ypos; // reversed since y-coordinates range from bottom to top
  lastX = xpos;
  lastY = ypos;

  cam.HandleMouseMove(xoffset, yoffset);
}

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(window, mouse_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glEnable(GL_DEPTH_TEST);

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();

  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330");

  Shader shaderProgram("res/shaders/rayMarching.vert",
                       "res/shaders/rayMarching.frag");

  int size = 2;
  Chunk chunks[size * size];

  for (int x = 0; x < size; x++) {
    for (int z = 0; z < size; z++) {
      chunks[x + z * size] = Chunk(glm::vec3(x, 0.0, z), shaderProgram);
    }
  }



  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  while (!glfwWindowShouldClose(window)) {

    // update delta deltaTime
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    // input
    processInput(window, &cam);
    // rendering
    //
     // clear the screen with a green color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Another Window");   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked
    ImGui::Text("%.3fms  %.1ffps", deltaTime*1000, 1/deltaTime);
    ImGui::End();

    glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);

    for (int x = 0; x < size; x++) {
      for (int z = 0; z < size; z++) {
        chunks[x + z * size].Draw(&cam);
      }
    }


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // check events and swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  for (int x = 0; x < size; x++) {
    for (int z = 0; z < size; z++) {
      chunks[x + z * size].Terminate();
    }
  }
  glfwTerminate();
  return 0;
}
