#ifndef FRUSTUM_H
#define FRUSTUM_H


#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"

class Plane {
    public:
        glm::vec3 normal;
        float disToOrigin;

        Plane(){}
        Plane(glm::vec3 a_normal, float a_dis)
        {
            normal = a_normal;
            disToOrigin = a_dis;
        }
};

class Frustum {
    public:
    Plane nearFace;
    Plane farFace;
    Plane rightFace;
    Plane leftFace;
    Plane topface;
    Plane bottomFace;

    Frustum(Camera *cam, float aspect, float fovY, float zNear, float zFar)
    {
        const float halfVSide = zFar * tanf(fovY * .5f);
        const float halfHSide = halfVSide * aspect;
        const glm::vec3 frontMultFar = zFar * cam->front;

        nearFace = Plane(cam->pos + zNear * cam->front, cam->front );
        farFace = Plane(cam->pos + frontMultFar, -cam->front );
        rightFace = Plane(cam->pos,
                                glm::cross(frontMultFar - cam->right * halfHSide, cam->up) );
        leftFace = Plane(cam->pos,
                                glm::cross(cam->up,frontMultFar + cam->right * halfHSide) );
        topFace = Plane(cam->pos,
                                glm::cross(cam->right, frontMultFar - cam->up * halfVSide) );
        bottomFace = Plane(cam->pos,
                                glm::cross(frontMultFar + cam->up * halfVSide, cam->right) );
    }
};

#endif