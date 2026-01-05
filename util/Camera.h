#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT };

class Camera {
public:
  glm::vec3 pos;
  glm::vec3 front;
  glm::vec3 up;
  glm::vec3 right;
  glm::vec3 worldUp;
  float nearPlane;
  float farPlane;
  float fovy;
  float ratio;
  float speed;
  float yaw;
  float pitch;
  float mouseSensitivity;

  Camera(glm::vec3 camPos)
      : pos(camPos), front(glm::vec3(0.0f, 0.0f, -1.0f)),
        up(glm::vec3(0.0f, 1.0f, 0.0f)), speed(2.5f),
        worldUp(glm::vec3(0.0f, 1.0f, 0.0f)) {
    UpdateVectors();
    yaw = -90.0f;
    pitch = 0.0f;
    mouseSensitivity = 0.1f;
    nearPlane = 0.1f;
    farPlane = 100.0f;
    fovy = glm::radians(45.0f);
    ratio = 800.0f / 600.0f;
  }

  void HandleInput(Camera_Movement direction, float deltaTime) {
    float vel = speed * deltaTime;
    if (direction == FORWARD)
      pos += front * vel;
    if (direction == BACKWARD)
      pos -= front * vel;
    if (direction == LEFT)
      pos -= right * vel;
    if (direction == RIGHT)
      pos += right * vel;
  }

  void HandleMouseMove(float xOff, float yOff) {
    xOff *= mouseSensitivity;
    yOff *= mouseSensitivity;

    yaw += xOff;
    pitch += yOff;

    if (pitch > 89.0f)
      pitch = 89.0f;
    if (pitch < -89.0f)
      pitch = -89.0f;

    UpdateVectors();
  }

private:
  void UpdateVectors() {
    // calculate the new Front vector
    glm::vec3 Front;
    Front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    Front.y = sin(glm::radians(pitch));
    Front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(Front);
    // also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(
        front, worldUp)); // normalize the vectors, because their length gets
                          // closer to 0 the more you look up or down which
                          // results in slower movement.
    up = glm::normalize(glm::cross(right, front));
  }
};

#endif
