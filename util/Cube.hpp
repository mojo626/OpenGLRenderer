#ifndef CUBE_H
#define CUBE_H

#include "Camera.h"
#include "Perlin.h"
#include "Shaders.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

class Cube {
public:
  Shader shader;
  glm::vec3 pos;

  Cube() {}
  Cube(glm::vec3 position, Shader thisShader) {
    shader = thisShader;
    pos = position;

    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

        -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

    std::vector<uint8_t> voxels = GenerateVoxels(glm::vec3(10, 10, 10));

    // create vertex buffer
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // bind vertex buffer to GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // set buffer data
    // use GL_DYNAMIC_DRAW if buffer data will be changing often
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenTextures(1, &texture3D);
    glBindTexture(GL_TEXTURE_3D, texture3D);

    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);

    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, 10, 10, 10, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, voxels.data());
    glGenerateMipmap(GL_TEXTURE_3D);

    shader.use();

    // 0: which parameter we are talking about
    // 3: size fo vertex attrib (vec3)
    // GL_FLOAT: type of data
    // GL_FALSE: whether the data is normalized
    // 3 * sizeof(float): this is the stride, and is distance in bytes between
    // each different vertex (void*)0: offset of start of data
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
  }

  void Draw(Camera *cam) {
    glEnable(GL_TEXTURE_3D);
    // bind texture
    // glBindTexture(GL_TEXTURE_2D, texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_3D, texture3D);

    unsigned int texLoc = glGetUniformLocation(shader.ID, "voxelShape");
    glUniform1i(texLoc, 0);

    shader.use();
    shader.setVec3("camPos", cam->pos);
    shader.setVec3("cubePosition", pos);

    // preform matrix math
    // model matrix
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    glm::mat4 view = glm::mat4(1.0f);
    // note that we're translating the scene in the reverse direction of where
    // we want to move
    view = glm::lookAt(cam->pos, cam->pos + cam->front, cam->up);
    glm::mat4 projection = glm::mat4(1.0f);
    projection =
        glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    // send matricies to shader
    int modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    int viewLoc = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int projLoc = glGetUniformLocation(shader.ID, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
  }

  void Terminate() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
  }

private:
  unsigned int VBO, VAO, EBO;
  unsigned int texture3D;
  std::vector<uint8_t> GenerateVoxels(glm::vec3 size) {
    std::vector<uint8_t> voxels(size.x * size.y * size.z * 4);
    Perlin p;

    for (int x = 0; x < size.x; x++) {
      for (int z = 0; z < size.z; z++) {
        //float noise = p.noise(x / 30.0 + pos.x, z / 30.0 + pos.z, 0.0) + 0.5;

        for (int y = 0; y < size.y; y++) {
          int id = 4 * (z * size.x * size.y + y * size.x + x);

          float noise = p.noise((x + pos.x*size.x)/40.0, (y + pos.y*size.y)/40.0, (z + pos.z*size.z)/40.0) + 0.5;

          voxels[id] = (int)((x + pos.x*size.x)/200*255);
          voxels[id + 1] = (int)((y + pos.y*size.y)/200*255); // Green channel
          voxels[id + 2] = (int)((z + pos.z*size.z)/200*255); // Blue channel
          voxels[id + 3] = static_cast<uint8_t>(noise > 0.5 ? 255 : 0); // Alpha channel (fully opaque)
        }
      }
     //std::cout << pos.x*size.x + x <<std::endl;
    }

    return voxels;
  }
};

#endif
