#version 460

in vec3 positionIn;
out vec3 positionOut;

uniform mat4 mvp;

void main(void)
{
    positionOut = positionIn;
    gl_Position = mvp * vec4(positionIn, 1.0);
}