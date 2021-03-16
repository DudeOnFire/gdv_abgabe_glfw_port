#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include "Shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>


class Rebelbase
{
public:
	//Shader
	Shader baseShader;

	glm::vec3 calcNorm(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);

	void calcSides(GLfloat& x, GLfloat& z, GLfloat speedMod, GLfloat rotation);

	//initial for setups
	void initialDraw(glm::mat4 mView, glm::vec3 lightPos, glm::vec3 camPos);
	void loadTextures();

	void drawBaseSetup(GLfloat scale);
	void redrawBase();

	void drawBase();

	unsigned int baseVBO;
	GLuint baseVAO;
	unsigned int baseEBO;

	//texture
	unsigned int BaseTexture;


	

protected:

	//position
	GLfloat baseXPosition = 8;
	GLfloat baseZPosition = 0;



	GLfloat mainBaseHight = 1.0;
	GLfloat mainHalfeHight = mainBaseHight / 2;
	GLfloat mainBaseWidth = 0.1 + baseZPosition;
	GLfloat mainBaseLength = 0.5;

	GLfloat sideBaseHight = 0.3;
	GLfloat sideBaseHalfeHight = sideBaseHight / 2;
	GLfloat sideBaseWidth = 0.5 + baseZPosition;
	GLfloat sideBaseLenght = 0.15;

private:


};

