#ifndef CHUNK_H
#define CHUNK_H

#include "Cube.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Shaders.hpp"
#include "Camera.h"

class Chunk {
    public:
    std::vector<Cube> cubes;
    glm::vec3 pos;
    int size;

    Chunk(){}
    Chunk(glm::vec3 position, Shader shaderProgram) {
        pos = position;

        size = 10;

        cubes = std::vector<Cube>(size * size * size);

        for (int x = 0; x < size; x++) {
            for (int z = 0; z < size; z++) {
                for (int y = 0; y < size; y++)
                {
                    cubes.at(x + z * size * size + y * size) = Cube(glm::vec3(x + size*pos.x, y + size*pos.y, z + size*pos.z), shaderProgram);
                }
            
            }
        }
    }

    void Draw(Camera *cam)
    {
        for (int x = 0; x < size; x++) {
            for (int z = 0; z < size; z++) {
                for (int y = 0; y < size; y++)
                {
                    if (!cubes.at(x + z * size * size + y * size).isEmpty)
                        cubes.at(x + z * size * size + y * size).Draw(cam);
                }
            
            }
        }
    }

    void Terminate()
    {
        for (int x = 0; x < size; x++) {
            for (int z = 0; z < size; z++) {
                for (int y = 0; y < size; y++)
                {
                    cubes.at(x + z * size * size + y * size).Terminate();
                }
            
            }
        }
    }
};


#endif