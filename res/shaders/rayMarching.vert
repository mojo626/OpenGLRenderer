#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec3 aColor;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 camPos;
uniform vec3 camDir;
uniform vec3 camUp;
uniform vec3 camRight;

out vec3 fDir;
out vec3 fPos;
out vec3 fUp;
out vec3 fRight;
out vec3 worldPos;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    fDir = camDir;
    //fDir = camPos - (inverse(model * view) * vec4(vec3(0), 1)).xyz;
    fPos = camPos;
    fUp = camUp;
    fRight = camRight;
    worldPos = (vec4(aPos, 1.0) * model).xyz;
}
