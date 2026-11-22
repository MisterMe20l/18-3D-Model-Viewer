#version 460

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float attenuationConst;
    float attenuationLinear;
    float attenuationQuad;
};

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Light light;
uniform Material material;
uniform vec3 cameraPosition;

in vec3 normalOut;
in vec3 positionOut;
in vec2 texCoordOut;

uniform sampler2D textureImage;

// Standard value for srgb
const float gamma = 2.2;

vec3 toLinear(vec3 _srgbColor)
{
    return pow(_srgbColor, vec3(gamma));
}

vec4 toLinear(vec4 _srgbColor)
{
    return pow(_srgbColor, vec4(gamma));
}

vec3 tosrgb(vec3 _linearColor)
{
    return pow(_linearColor, vec3(1.0 / gamma));
}

vec4 tosrgb(vec4 _linearColor)
{
    return pow(_linearColor, vec4(1.0 / gamma));
}

vec3 calcAmbient(Light _light, Material _material)
{
    return toLinear(_light.ambient * _material.ambient);
}

vec3 calcDiffuse(Light _light, Material _material)
{
    vec3 normal = normalize(normalOut);
    vec3 lightDirection = normalize(_light.position - positionOut);
    float lightIntensity = max(dot(lightDirection, normal), 0.0);
    return toLinear(_light.diffuse * _material.diffuse) * lightIntensity;
}

vec3 calcSpecular(Light _light, Material _material)
{
    vec3 normal = normalize(normalOut);
    vec3 lightDirection = normalize(_light.position - positionOut);
    vec3 viewDirection = normalize(cameraPosition - positionOut);
    vec3 reflexion = reflect(-lightDirection, normal);
    float specularTerm = pow(max(dot(viewDirection, reflexion), 0.0), _material.shininess);
    return toLinear(_light.specular * _material.specular) * specularTerm;
}

float calcAttenuation(Light _light)
{
    float dist = length(_light.position - positionOut);
    return (1.0 / (_light.attenuationConst + (_light.attenuationLinear * dist) + (_light.attenuationQuad * dist * dist)));
}

void main(void)
{
    vec3 ambientColor = calcAmbient(light, material);
    vec3 diffuseColor = calcDiffuse(light, material);
    vec3 specularColor = calcSpecular(light, material);
    float attenuation = calcAttenuation(light);

    vec4 color = vec4(attenuation * (ambientColor + diffuseColor + specularColor), 1.0);

    vec4 srgbTexColor = texture(textureImage, texCoordOut);
    vec4 linearTexColor = toLinear(srgbTexColor);

    gl_FragColor = tosrgb(color * linearTexColor);
}