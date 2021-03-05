#version 330 core
out vec4 FragColor;
  
struct Light {
    vec3 position;
    vec3 direction;
    vec3 color;
    float cutOff;
    float outerCutOff;
};

in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform Light light;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightDirection;
uniform vec3 viewPos;
uniform sampler2D ourTexture;

vec3 calculateFlashlight(){

    // Ambient
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * light.color;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.color;

    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0f);
    vec3 specular = spec * light.color;

    // Flashlight calculations
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    diffuse *= intensity;
    specular *= intensity;

    vec3 result = ambient + diffuse + specular;
    return result;
}


void main()
{

    // Ambient lighting
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;


    // Diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightDirection);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    

    // Specular lighting
    float specularStrength = 1.0;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3  specular = specularStrength * spec * lightColor;


    vec3 result = ambient + diffuse;
    FragColor = texture(ourTexture, TexCoord) * vec4(result, 1.0f);
}