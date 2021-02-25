#pragma once

#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "stb_image.h"

#include <iostream>
#include <vector>
#include "Shader.h"


// Class to draw a cubemap
class Skybox {

public:

	Shader skyboxShader;
	unsigned int skyboxVAO, skyboxVBO;

	void drawSkybox(glm::mat4 mView, unsigned int cubemapTexture);
	unsigned int loadSkybox();

private:

	unsigned int createSkybox(std::vector<std::string> faces);
	unsigned int loadTexture(char const* path);

};