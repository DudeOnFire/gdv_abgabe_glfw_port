#pragma once

#include <glad/glad.h>
#include <iostream>
#include "Shader.h"
#include "stb_image.h"


class Landscape {

public:

	Shader landscapeShader;
	unsigned int scapeVBO, scapeEBO, snowTexture;
	GLuint scapeVAO;

	void loadLandscape();
	void drawLandscape();

};