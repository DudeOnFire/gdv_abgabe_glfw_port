#pragma once

#include <glad/glad.h>
#include <iostream>
#include "Shader.h"
#include "stb_image.h"
#include "Include/glm/gtc/matrix_transform.hpp"


class Landscape {

public:

	Shader landscapeShader;
	unsigned int scapeVBO, scapeEBO, snowTexture;
	GLuint scapeVAO;

	void loadLandscape();
	void drawLandscape(glm::mat4 mView, glm::vec3 lightPos, glm::vec3 camPos);
	unsigned int loadTexture(const char* path);

};