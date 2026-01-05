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
#include "Gradient.hpp"
#include "FastNoiseLite.h"

class Cube {
public:
  Shader shader;
  glm::vec3 pos;
  bool isEmpty;

  Cube() {}
  Cube(glm::vec3 position, Shader thisShader) {
    shader = thisShader;
    pos = position;
    isEmpty = true;

    

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     

     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
   

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};



    std::vector<uint8_t> voxels = GenerateTerrain(glm::vec3(10, 10, 10));

    if (isEmpty)
      return;

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
  }

  void Draw(Camera *cam) {
    //Don't render if the camera cannot see it
    if (RadarFrustumCull(cam))
    {
      return;
    }


    glEnable(GL_TEXTURE_3D);
    // bind texture
    // glBindTexture(GL_TEXTURE_2D, texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_3D, texture3D);

    unsigned int texLoc = glGetUniformLocation(shader.ID, "voxelShape");
    glUniform1i(texLoc, 0);

    shader.use();
    shader.setVec3("camPos", cam->pos);
    shader.setVec3("camDir", cam->front);
    shader.setVec3("cubePosition", pos);

    // preform matrix math
    // model matrix
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::scale(model, glm::vec3(0.9999, 0.9999, 0.9999));
    glm::mat4 view = glm::mat4(1.0f);
    // note that we're translating the scene in the reverse direction of where
    // we want to move
    view = glm::lookAt(cam->pos, cam->pos + cam->front, cam->up);
    glm::mat4 projection = glm::mat4(1.0f);
    projection =
        glm::perspective(cam->fovy, cam->ratio, cam->nearPlane, cam->farPlane);

    // send matricies to shader
    int modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    int viewLoc = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int projLoc = glGetUniformLocation(shader.ID, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    //glBindVertexArray(VAO);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
  }
  bool RadarFrustumCull(Camera *cam)
    {
      float size = 1.0f;
      float error = 1.0f;
        glm::vec3 points[] = {
            glm::vec3(size + pos.x * size, 0.0f + pos.y * size, 0.0f + pos.z * size),
            glm::vec3(size + pos.x * size, 0.0f + pos.y * size, size + pos.z * size),
            glm::vec3(size + pos.x * size, size + pos.y * size, 0.0f + pos.z * size),
            glm::vec3(size + pos.x * size, size + pos.y * size, size + pos.z * size),
            glm::vec3(0.0f + pos.x * size, 0.0f + pos.y * size, size + pos.z * size),
            glm::vec3(0.0f + pos.x * size, 0.0f + pos.y * size, 0.0f + pos.z * size),
            glm::vec3(0.0f + pos.x * size, size + pos.y * size, 0.0f + pos.z * size),
            glm::vec3(0.0f + pos.x * size, size + pos.y * size, size + pos.z * size)
        };

        for (int i = 0; i < 8; i++)
        {
            glm::vec3 p = points[i];

            glm::vec3 v = p - cam->pos;
            float pcZ = glm::dot(v, cam->front);

            if (pcZ > cam->farPlane + error || pcZ < cam->nearPlane - error)
                continue;

            float pcX = glm::dot(v, cam->right);
            float pcY = glm::dot(v, cam->up);
            float h = pcZ * 2  * tan(cam->fovy/2);

            if (-h/2 - error > pcY || h/2 + error  < pcY)
                continue;
            
            float w = h * cam->ratio;

            if (-w/2 - error  > pcX || w/2 + error  < pcX)
                continue;
            

            return false;
        }

        return true;
    }

  void Terminate() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
  }

private:
  unsigned int VBO, VAO, EBO;
  unsigned int texture3D;
  std::vector<uint8_t> GenerateVoxels3D(glm::vec3 size) {
    std::vector<uint8_t> voxels(size.x * size.y * size.z * 4);
    Perlin p;

    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetFractalOctaves(5);
    

    for (int x = 0; x < size.x; x++) {
      for (int z = 0; z < size.z; z++) {
        //float noise = p.noise(x / 30.0 + pos.x, z / 30.0 + pos.z, 0.0) + 0.5;

        for (int y = 0; y < size.y; y++) {
          int id = 4 * (z * size.x * size.y + y * size.x + x);

          float noise_val = noise.GetNoise((x + pos.x*size.x), (y + pos.y*size.y), (z + pos.z*size.z));
          //std::cout << noise_val << std::endl;

          voxels[id] = (int)((x + pos.x*size.x)/200*255);
          voxels[id + 1] = (int)((y + pos.y*size.y)/200*255); // Green channel
          voxels[id + 2] = (int)((z + pos.z*size.z)/200*255); // Blue channel
          voxels[id + 3] = static_cast<uint8_t>(noise_val > 0.0 ? 255 : 0); // Alpha channel (fully opaque)
        }
      }
     //std::cout << pos.x*size.x + x <<std::endl;
    }

    return voxels;
  }

  std::vector<uint8_t> GenerateTerrain(glm::vec3 size) {
    std::vector<uint8_t> voxels(size.x * size.y * size.z * 4);
    Perlin p;
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetFractalOctaves(5);

    std::vector<GradientColor> colors;
    colors.push_back(GradientColor(glm::vec3(0.0, 0.0, 1.0), 0.0));
    colors.push_back(GradientColor(glm::vec3(0.85, 0.58, 0.27), 0.1));
    colors.push_back(GradientColor(glm::vec3(0.0, 1.0, 0.0), 0.2));
    colors.push_back(GradientColor(glm::vec3(0.5, 0.5, 0.5), 0.8));
    colors.push_back(GradientColor(glm::vec3(1.0, 1.0, 1.0), 0.9));
    Gradient gradient(colors);

    for (int x = 0; x < size.x; x++) {
      for (int z = 0; z < size.z; z++) {
        //float noise = p.noise((x + pos.x*size.x)/40.0, 0.0, (z + pos.z*size.z)/40.0) + 0.5;
        float noise_val = noise.GetNoise((x + pos.x*size.x), (z + pos.z*size.z))/2+0.5;

        for (int y = 0; y < size.y; y++) {
          int id = 4 * (z * size.x * size.y + y * size.x + x);

          //float noise = p.noise((x + pos.x*size.x)/40.0, (y + pos.y*size.y)/40.0, (z + pos.z*size.z)/40.0) + 0.5;

          glm::vec3 color = gradient.GetColor((y + pos.y * size.y)/100.0f);

          voxels[id] = (int)(color.x*255);
          voxels[id + 1] = (int)(color.y*255); // Green channel
          voxels[id + 2] = (int)(color.z*255); // Blue channel
          voxels[id + 3] = static_cast<uint8_t>(noise_val*30 > y + pos.y * size.y ? 255 : 0); // Alpha channel (fully opaque)

          if (noise_val*30 > y + pos.y * size.y)
            isEmpty = false;
        }
      }
    }

    return voxels;
  }
};

#endif
