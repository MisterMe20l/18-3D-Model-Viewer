#version 460

in vec3 positionOut;
in vec3 normalOut;
in vec2 texCoordOut;

out vec4 FragColor;

uniform sampler2D texture_diffuse;
uniform vec3 lightDir = normalize(vec3(-0.5, -1.0, -0.3)); // Default light
uniform vec3 lightColor = vec3(1.0);
uniform vec3 ambientColor = vec3(0.2);

void main()
{
    vec4 texColor = texture(texture_diffuse, texCoordOut);

    // Basic diffuse lighting
    float diff = max(dot(normalize(normalOut), -lightDir), 0.0);
    vec3 finalColor = texColor.rgb * (ambientColor + diff * lightColor);

    FragColor = vec4(finalColor, texColor.a);
}
