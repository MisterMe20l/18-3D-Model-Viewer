#version 460

vec3 colorA = vec3(1.0, 0.0, 0.0);
vec3 colorB = vec3(0.0, 0.0, 1.0);

in vec3 positionOut;

out vec4 pixelColor;

void main(void)
{
    vec3 mixcolor = mix(colorA, colorB, positionOut.y);
    gl_FragColor = vec4(mixcolor, 1.0);
}