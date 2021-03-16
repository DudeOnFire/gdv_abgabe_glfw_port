#version 330 core


in GS_OUT {
	vec3 ourColor;
	vec2 TexCoord;
	vec3 normal;
    vec3 FragPos;
} fs_in;

out vec4 FragColor;

uniform sampler2D greymetallightTexture;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightDirection;
uniform vec3 viewPos;

void main(void)
{
	// Lighting
	float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse lighting
    vec3 norm = normalize(fs_in.normal);
    vec3 lightDir = normalize(lightDirection);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular lighting
    float specularStrength = 0.8;
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3  specular = specularStrength * spec * lightColor;



    vec3 result = (ambient + diffuse + specular);
	FragColor = texture(greymetallightTexture, fs_in.TexCoord) * vec4(result, 1.0f);
}