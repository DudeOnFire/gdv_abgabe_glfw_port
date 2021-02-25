#pragma once

#include <glad/glad.h>
#include "Include/glm/glm.hpp"
#include "Include/glm/gtc/matrix_transform.hpp"

#include <iostream>
#include "Shader.h"



class Lighting {

public:

	// Variables
	unsigned int lightCubeVAO, VBO, cubeVAO;
	Shader lightingShader;
	Shader lightCubeShader;

	// Functions
	void generateLight(glm::mat4 mView, glm::vec3 lightPos, glm::vec3 camPos);
	void prepareLight();

};