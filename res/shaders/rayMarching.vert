#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 cubePosition;

uniform vec3 camPos;



out vec3 fPos;
out vec3 cubePos;
out vec3 worldPos;
out vec3 normal;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    fPos = camPos;
    cubePos = cubePosition;
    worldPos = (vec4(aPos, 1.0) * model).xyz;
    normal = aNormal;
}

