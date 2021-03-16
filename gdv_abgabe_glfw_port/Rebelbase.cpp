#include "Rebelbase.h"



glm::vec3 Rebelbase::calcNorm(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
	//aus 3 Punkten 2 Vectoren bilden, von diesen beiden das Kreuzprodukt bilden
	glm::vec3 u = p2 - p1;
	glm::vec3 v = p3 - p1;
	glm::vec3 normal = glm::cross(u, v);
	return normal;
}

void Rebelbase::calcSides(GLfloat& x, GLfloat& z, GLfloat speedMod, GLfloat rotation) {
	GLfloat mov = speedMod;

	//the 3 angles for the triangle
	GLfloat alpha = rotation;
	GLfloat beta = 0;
	GLfloat gamma = 90;

	//the sides of the triangle
	GLfloat a = 0;
	GLfloat b = 0;

	//linksdrehung die ersten 90Grad || rechtsdrehung f?r die letzten 90 Grad => +X -Z
	if ((alpha >= 0 && alpha <= 90) || (alpha <= -270 && alpha >= -360)) {
		if (alpha >= 0) {
			beta = 180 - gamma - alpha;
		}
		else {
			beta = 180 - gamma - (alpha + 360);
		}

		a = (mov / glm::sin(glm::radians(gamma))) * glm::sin(glm::radians(alpha));
		b = (mov / glm::sin(glm::radians(gamma))) * glm::sin(glm::radians(beta));

		x = b;
		z = -a;
	}
	//linksdrehung der 2. 90 Grad || rechtsdrehung f?r die 3. 90 Grad => -X -Z
	else if ((alpha >= 90 && alpha <= 180) || (alpha <= -180 && alpha >= -270)) {
		if (alpha >= 0) {
			beta = 180 - gamma - (alpha - 90);
			alpha = alpha - 90;
		}
		else {
			beta = 180 - gamma - (alpha + 270);
			alpha = alpha + 270;
		}

		a = (mov / glm::sin(glm::radians(gamma))) * glm::sin(glm::radians(alpha));
		b = (mov / glm::sin(glm::radians(gamma))) * glm::sin(glm::radians(beta));

		x = -a;
		z = -b;
	}
	//linksdrehung der 3. 90 Grad || rechtsdrehung f?r die 2. 90 Grad => -X Z
	else if ((alpha >= 180 && alpha <= 270) || (alpha <= -90 && alpha >= -180)) {
		if (alpha >= 0) {
			beta = 180 - gamma - (alpha - 180);
			alpha = alpha - 180;
		}
		else {
			beta = 180 - gamma - (alpha + 180);
			alpha = alpha + 180;
		}

		a = (mov / glm::sin(glm::radians(gamma))) * glm::sin(glm::radians(alpha));
		b = (mov / glm::sin(glm::radians(gamma))) * glm::sin(glm::radians(beta));

		x = -b;
		z = a;
	}

	//linksdrehung der 4. 90 Grad ||rechtsdrehung f?r die 1. 90 Grad => X Z
	else if ((alpha >= 270 && alpha <= 360) || (alpha <= -0 && alpha >= -90)) {
		if (alpha >= 0) {
			beta = 180 - gamma - (alpha - 270);
			alpha = alpha - 270;
		}
		else {
			beta = 180 - gamma - (alpha + 90);
			alpha = alpha + 90;
		}

		a = (mov / glm::sin(glm::radians(gamma))) * glm::sin(glm::radians(alpha));
		b = (mov / glm::sin(glm::radians(gamma))) * glm::sin(glm::radians(beta));

		x = a;
		z = b;
	}
}


void Rebelbase::initialDraw(glm::mat4 mView, glm::vec3 lightPos, glm::vec3 camPos) {
	glm::mat4 model = glm::mat4(1.0f);
	baseShader.use();
	baseShader.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
	baseShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	baseShader.setVec3("lightDirection", lightPos);
	baseShader.setVec3("viewPos", camPos);

	// View/Projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)2100 / (float)1200, 0.1f, 100.0f);
	glm::mat4 view = mView;
	baseShader.setMat4("projection", projection);
	baseShader.setMat4("view", view);

	model = glm::mat4(1.0f);
	//model = glm::rotate(model, glm::radians((float)60), glm::vec3(0.0, 1.0, 0.0));
	//model = glm::translate(model, glm::vec3(0, -0.1f, 0));
	//baseShader.setMat4("model", model);
	//model = glm::translate(model, glm::vec3(5, 0, 0) );
	baseShader.setMat4("model", model);

	model = glm::translate(model, glm::vec3(1.0f, 0, 1));
	baseShader.setMat4("model", model);

	drawBaseSetup(2);


}

void Rebelbase::loadTextures() {
	glGenTextures(1, &BaseTexture);
	glBindTexture(GL_TEXTURE_2D, BaseTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	//unsigned char* data = SOIL_load_image("resources/greymetal.jpg", &width, &height, &nrChannels, 0);
	unsigned char* data = stbi_load("resources/greymetallight.jpg", &width, &height, &nrChannels, 0);

	if (data) {
		std::cout << "data is valid" << std::endl;

		//The crash problem is probably caused by glTexImage2D reading past the bounds of your data buffer.

		//glPixelStorei sets pixel storage modes that affect the operation of subsequent glReadPixels
		//as well as the unpacking of texture patterns (see glTexImage2D and glTexSubImage2D).

		//Specifies the alignment requirements for the start of each pixel row in memory. The allowable values are
		//1 (byte-alignment), 2 (rows aligned to even-numbered bytes), 4 (word-alignment), and 8 (rows start on double-word boundaries).
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load greymetallightTexture" << std::endl;
	}

	stbi_image_free(data);
}

void Rebelbase::drawBaseSetup(GLfloat scale) {

	float vertices[] = {

		//oberseite
		(baseXPosition)*scale,(mainBaseHight)*scale,(-mainBaseWidth)* scale,						1.0, 1.0, 1.0,		1.0, 1.0,
		(baseXPosition)*scale,(mainBaseHight)*scale,(mainBaseWidth)*scale,							1.0, 1.0, 1.0,		0.0, 1.0,
		(baseXPosition + mainBaseLength)* scale,(mainBaseHight)*scale,(mainBaseWidth)*scale,		1.0, 1.0, 1.0,		0.0, 0.0,
		(baseXPosition + mainBaseLength)* scale,(mainBaseHight)*scale,(-mainBaseWidth)* scale,		1.0, 1.0, 1.0,		1.0, 0.0,

		//schräg hinten
		(baseXPosition + mainBaseLength + mainBaseLength)* scale,(mainHalfeHight)* scale,(-mainBaseWidth)* scale,		1.0, 1.0, 1.0,		1.0, 0.0,
		(baseXPosition + mainBaseLength + mainBaseLength)* scale,(mainHalfeHight)* scale,(mainBaseWidth)* scale,		1.0, 1.0, 1.0,		0.0, 0.0,
		(baseXPosition + mainBaseLength)* scale,(mainBaseHight)*scale,(mainBaseWidth)* scale,							1.0, 1.0, 1.0,		0.0, 1.0,
		(baseXPosition + mainBaseLength)* scale,(mainBaseHight)*scale,(-mainBaseWidth)* scale,							1.0, 1.0, 1.0,		1.0, 1.0,

		//schräg vorne
		(baseXPosition)*scale,(mainBaseHight)*scale,(-mainBaseWidth)* scale,						1.0, 1.0, 1.0,		1.0, 1.0,
		(baseXPosition)*scale,(mainBaseHight)*scale,(mainBaseWidth)*scale,							1.0, 1.0, 1.0,		0.0, 1.0,
		(baseXPosition - mainBaseLength)* scale,(mainHalfeHight)*scale,(mainBaseWidth)*scale,			1.0, 1.0, 1.0,		0.0, 0.0,
		(baseXPosition - mainBaseLength)* scale,(mainHalfeHight)*scale,(-mainBaseWidth)* scale,		1.0, 1.0, 1.0,		1.0, 0.0,

		//seite hinten
		(baseXPosition + mainBaseLength + mainBaseLength)* scale,(mainHalfeHight)*scale,(-mainBaseWidth)* scale,		1.0, 1.0, 1.0,		1.0, 0.0,
		(baseXPosition + mainBaseLength + mainBaseLength)* scale,(0)* scale,(-mainBaseWidth)* scale,					1.0, 1.0, 1.0,		0.0, 0.0,
		(baseXPosition + mainBaseLength + mainBaseLength)* scale,(0)* scale,(mainBaseWidth)*scale,						1.0, 1.0, 1.0,		0.0, 1.0,
		(baseXPosition + mainBaseLength + mainBaseLength)* scale,(mainHalfeHight)*scale,(mainBaseWidth)*scale,			1.0, 1.0, 1.0,		1.0, 1.0,

		//seite vorne
		(baseXPosition - mainBaseLength)* scale,(mainHalfeHight)*scale,(mainBaseWidth)*scale,		1.0, 1.0, 1.0,		1.0, 1.0,
		(baseXPosition - mainBaseLength)* scale,(0)* scale,(mainBaseWidth)*scale,					1.0, 1.0, 1.0,		0.0, 1.0,
		(baseXPosition - mainBaseLength)* scale,(0)* scale,(-mainBaseWidth)* scale,					1.0, 1.0, 1.0,		0.0, 0.0,
		(baseXPosition - mainBaseLength)* scale,(mainHalfeHight)*scale,(-mainBaseWidth)* scale,		1.0, 1.0, 1.0,		1.0, 0.0,
		  
		//========== seiten ==========

		//seite rechts
		(baseXPosition + mainBaseLength + mainBaseLength)* scale,(0)* scale,(mainBaseWidth)*scale,					1.0, 1.0, 1.0,		1.0, 0.0,
		(baseXPosition - mainBaseLength)* scale,(0)* scale,(mainBaseWidth)*scale,									1.0, 1.0, 1.0,		0.0, 0.0,
		(baseXPosition - mainBaseLength)* scale,(mainHalfeHight)*scale,(mainBaseWidth)*scale,						1.0, 1.0, 1.0,		0.0, 1.0,
		(baseXPosition + mainBaseLength + mainBaseLength)* scale,(mainHalfeHight)*scale,(mainBaseWidth)*scale,		1.0, 1.0, 1.0,		1.0, 1.0,


		//seite links
		(baseXPosition + mainBaseLength + mainBaseLength)* scale,(mainHalfeHight)*scale,(-mainBaseWidth)* scale,	1.0, 1.0, 1.0,		1.0, 1.0,
		(baseXPosition - mainBaseLength)* scale,(mainHalfeHight)*scale,(-mainBaseWidth)* scale,						1.0, 1.0, 1.0,		0.0, 1.0,
		(baseXPosition - mainBaseLength)* scale,(0)* scale,(-mainBaseWidth)* scale,									1.0, 1.0, 1.0,		0.0, 0.0,
		(baseXPosition + mainBaseLength + mainBaseLength)* scale,(0)* scale,(-mainBaseWidth)* scale,					1.0, 1.0, 1.0,		1.0, 0.0,

		//dreieck hinten links
		(baseXPosition)* scale,(mainHalfeHight)*scale,(-mainBaseWidth)* scale,						1.0, 1.0, 1.0,		1.0, 0.0,
		(baseXPosition)*scale,(mainBaseHight)*scale,(-mainBaseWidth)* scale,						1.0, 1.0, 1.0,		1.0, 1.0,
		(baseXPosition - mainBaseLength)* scale,(mainHalfeHight)*scale,(-mainBaseWidth)* scale,		1.0, 1.0, 1.0,		0.0, 0.0,

		//dreieck hinten rechts
		(baseXPosition - mainBaseLength)* scale,(mainHalfeHight)*scale,(mainBaseWidth)* scale,		1.0, 1.0, 1.0,		0.0, 0.0,
		(baseXPosition)*scale,(mainBaseHight)*scale,(mainBaseWidth)* scale,							1.0, 1.0, 1.0,		1.0, 1.0,
		(baseXPosition)*scale,(mainHalfeHight)*scale,(mainBaseWidth)* scale,						1.0, 1.0, 1.0,		1.0, 0.0,

		//dreieck vorne rechts
		(baseXPosition + mainBaseLength)* scale,(mainHalfeHight)*scale,(mainBaseWidth)*scale,						1.0, 1.0, 1.0,		1.0, 0.0,
		(baseXPosition + mainBaseLength)* scale,(mainBaseHight)*scale,(mainBaseWidth)*scale,						1.0, 1.0, 1.0,		1.0, 1.0,
		(baseXPosition + mainBaseLength + mainBaseLength)* scale,(mainHalfeHight)*scale,(mainBaseWidth)*scale,		1.0, 1.0, 1.0,		0.0, 0.0,

		//dreieck vorne links
		(baseXPosition + mainBaseLength + mainBaseLength)* scale,(mainHalfeHight)*scale,(-mainBaseWidth)* scale,		1.0, 1.0, 1.0,		0.0, 0.0,
		(baseXPosition + mainBaseLength)* scale,(mainBaseHight)*scale,(-mainBaseWidth)* scale,						1.0, 1.0, 1.0,		1.0, 1.0,
		(baseXPosition + mainBaseLength)* scale,(mainHalfeHight)*scale,(-mainBaseWidth)* scale,						1.0, 1.0, 1.0,		1.0, 0.0,

		//rechteck rechts
		(baseXPosition + mainBaseLength)* scale,(mainHalfeHight)*scale,(mainBaseWidth)*scale,		1.0, 1.0, 1.0,		1.0, 0.0,
		(baseXPosition)*scale,(mainHalfeHight)*scale,(mainBaseWidth)*scale,							1.0, 1.0, 1.0,		0.0, 0.0,
		(baseXPosition)*scale,(mainBaseHight)*scale,(mainBaseWidth)*scale,							1.0, 1.0, 1.0,		0.0, 1.0,
		(baseXPosition + mainBaseLength)* scale,(mainBaseHight)*scale,(mainBaseWidth)*scale,		1.0, 1.0, 1.0,		1.0, 1.0,

		//rechteck links
		(baseXPosition + mainBaseLength)* scale,(mainBaseHight)*scale,(-mainBaseWidth)*scale,		1.0, 1.0, 1.0,		1.0, 1.0,
		(baseXPosition)*scale,(mainBaseHight)*scale,(-mainBaseWidth)*scale,							1.0, 1.0, 1.0,		0.0, 1.0,
		(baseXPosition)*scale,(mainHalfeHight)*scale,(-mainBaseWidth)*scale,						1.0, 1.0, 1.0,		0.0, 0.0,
		(baseXPosition + mainBaseLength)* scale,(mainHalfeHight)*scale,(-mainBaseWidth)*scale,		1.0, 1.0, 1.0,		1.0, 0.0,




		// ========== ========== Seitenteil ========== ==========
		//oberseite
		(baseXPosition + sideBaseLenght)*scale,(sideBaseHight)*scale,(-sideBaseWidth)* scale,						1.0, 1.0, 1.0,		1.0, 1.0,
		(baseXPosition + sideBaseLenght)*scale,(sideBaseHight)*scale,(sideBaseWidth)*scale,							1.0, 1.0, 1.0,		0.0, 1.0,
		(baseXPosition + sideBaseLenght + sideBaseLenght)* scale,(sideBaseHight)*scale,(sideBaseWidth)*scale,		1.0, 1.0, 1.0,		0.0, 0.0,
		(baseXPosition + sideBaseLenght + sideBaseLenght)* scale,(sideBaseHight)*scale,(-sideBaseWidth)* scale,		1.0, 1.0, 1.0,		1.0, 0.0,

		//schräg hinten
		(baseXPosition + sideBaseLenght + sideBaseLenght + sideBaseLenght)* scale,(sideBaseHalfeHight)*scale,(-sideBaseWidth)* scale,		1.0, 1.0, 1.0,		1.0, 0.0,
		(baseXPosition + sideBaseLenght + sideBaseLenght + sideBaseLenght)* scale,(sideBaseHalfeHight)*scale,(sideBaseWidth)*scale,		1.0, 1.0, 1.0,		0.0, 0.0,
		(baseXPosition + sideBaseLenght + sideBaseLenght)* scale,(sideBaseHight)*scale,(sideBaseWidth)*scale,							1.0, 1.0, 1.0,		0.0, 1.0,
		(baseXPosition + sideBaseLenght + sideBaseLenght)* scale,(sideBaseHight)*scale,(-sideBaseWidth)* scale,							1.0, 1.0, 1.0,		1.0, 1.0,

		//schräg vorne
		(baseXPosition + sideBaseLenght)*scale,(sideBaseHight)*scale,(-sideBaseWidth)* scale,						1.0, 1.0, 1.0,		1.0, 1.0,
		(baseXPosition + sideBaseLenght)*scale,(sideBaseHight)*scale,(sideBaseWidth)*scale,							1.0, 1.0, 1.0,		0.0, 1.0,
		(baseXPosition - sideBaseLenght + sideBaseLenght)* scale,(sideBaseHalfeHight)*scale,(sideBaseWidth)*scale,			1.0, 1.0, 1.0,		0.0, 0.0,
		(baseXPosition - sideBaseLenght + sideBaseLenght)* scale,(sideBaseHalfeHight)*scale,(-sideBaseWidth)* scale,		1.0, 1.0, 1.0,		1.0, 0.0,

		//seite hinten
		(baseXPosition + sideBaseLenght + sideBaseLenght + sideBaseLenght)* scale,(sideBaseHalfeHight)*scale,(-sideBaseWidth)* scale,		1.0, 1.0, 1.0,		1.0, 0.0,
		(baseXPosition + sideBaseLenght + sideBaseLenght + sideBaseLenght)* scale,(0)* scale,(-sideBaseWidth)* scale,					1.0, 1.0, 1.0,		0.0, 0.0,
		(baseXPosition + sideBaseLenght + sideBaseLenght + sideBaseLenght)* scale,(0)* scale,(sideBaseWidth)*scale,						1.0, 1.0, 1.0,		0.0, 1.0,
		(baseXPosition + sideBaseLenght + sideBaseLenght + sideBaseLenght)* scale,(sideBaseHalfeHight)*scale,(sideBaseWidth)*scale,			1.0, 1.0, 1.0,		1.0, 1.0,

		//seite vorne
		(baseXPosition - sideBaseLenght + sideBaseLenght)* scale,(sideBaseHalfeHight)*scale,(sideBaseWidth)*scale,		1.0, 1.0, 1.0,		1.0, 1.0,
		(baseXPosition - sideBaseLenght + sideBaseLenght)* scale,(0)* scale,(sideBaseWidth)*scale,					1.0, 1.0, 1.0,		0.0, 1.0,
		(baseXPosition - sideBaseLenght + sideBaseLenght)* scale,(0)* scale,(-sideBaseWidth)* scale,					1.0, 1.0, 1.0,		0.0, 0.0,
		(baseXPosition - sideBaseLenght + sideBaseLenght)* scale,(sideBaseHalfeHight)*scale,(-sideBaseWidth)* scale,		1.0, 1.0, 1.0,		1.0, 0.0,

		//========== seiten ==========

		//seite rechts
		(baseXPosition + sideBaseLenght + sideBaseLenght + sideBaseLenght)* scale,(0)* scale,(sideBaseWidth)*scale,					1.0, 1.0, 1.0,		1.0, 0.0,
		(baseXPosition - sideBaseLenght + sideBaseLenght)* scale,(0)* scale,(sideBaseWidth)*scale,									1.0, 1.0, 1.0,		0.0, 0.0,
		(baseXPosition - sideBaseLenght + sideBaseLenght)* scale,(sideBaseHalfeHight)*scale,(sideBaseWidth)*scale,						1.0, 1.0, 1.0,		0.0, 1.0,
		(baseXPosition + sideBaseLenght + sideBaseLenght + sideBaseLenght)* scale,(sideBaseHalfeHight)*scale,(sideBaseWidth)*scale,		1.0, 1.0, 1.0,		1.0, 1.0,


		//seite links
		(baseXPosition + sideBaseLenght + sideBaseLenght + sideBaseLenght)* scale,(sideBaseHalfeHight)*scale,(-sideBaseWidth)* scale,	1.0, 1.0, 1.0,		1.0, 1.0,
		(baseXPosition - sideBaseLenght + sideBaseLenght)* scale,(sideBaseHalfeHight)*scale,(-sideBaseWidth)* scale,						1.0, 1.0, 1.0,		0.0, 1.0,
		(baseXPosition - sideBaseLenght + sideBaseLenght)* scale,(0)* scale,(-sideBaseWidth)* scale,									1.0, 1.0, 1.0,		0.0, 0.0,
		(baseXPosition + sideBaseLenght + sideBaseLenght + sideBaseLenght)* scale,(0)* scale,(-sideBaseWidth)* scale,					1.0, 1.0, 1.0,		1.0, 0.0,

		//dreieck hinten links
		(baseXPosition + sideBaseLenght)*scale,(sideBaseHalfeHight)*scale,(-sideBaseWidth)* scale,						1.0, 1.0, 1.0,		1.0, 0.0,
		(baseXPosition + sideBaseLenght)*scale,(sideBaseHight)*scale,(-sideBaseWidth)* scale,						1.0, 1.0, 1.0,		1.0, 1.0,
		(baseXPosition - sideBaseLenght + sideBaseLenght)* scale,(sideBaseHalfeHight)*scale,(-sideBaseWidth)* scale,		1.0, 1.0, 1.0,		0.0, 0.0,

		//dreieck hinten rechts
		(baseXPosition - sideBaseLenght + sideBaseLenght)* scale,(sideBaseHalfeHight)*scale,(sideBaseWidth)*scale,		1.0, 1.0, 1.0,		0.0, 0.0,
		(baseXPosition + sideBaseLenght)*scale,(sideBaseHight)*scale,(sideBaseWidth)*scale,							1.0, 1.0, 1.0,		1.0, 1.0,
		(baseXPosition + sideBaseLenght)*scale,(sideBaseHalfeHight)*scale,(sideBaseWidth)*scale,						1.0, 1.0, 1.0,		1.0, 0.0,

		//dreieck vorne rechts
		(baseXPosition + sideBaseLenght + sideBaseLenght)* scale,(sideBaseHalfeHight)*scale,(sideBaseWidth)*scale,						1.0, 1.0, 1.0,		1.0, 0.0,
		(baseXPosition + sideBaseLenght + sideBaseLenght)* scale,(sideBaseHight)*scale,(sideBaseWidth)*scale,						1.0, 1.0, 1.0,		1.0, 1.0,
		(baseXPosition + sideBaseLenght + sideBaseLenght + sideBaseLenght)* scale,(sideBaseHalfeHight)*scale,(sideBaseWidth)*scale,		1.0, 1.0, 1.0,		0.0, 0.0,

		//dreieck vorne links
		(baseXPosition + sideBaseLenght + sideBaseLenght + sideBaseLenght)* scale,(sideBaseHalfeHight)*scale,(-sideBaseWidth)* scale,		1.0, 1.0, 1.0,		0.0, 0.0,
		(baseXPosition + sideBaseLenght + sideBaseLenght)* scale,(sideBaseHight)*scale,(-sideBaseWidth)* scale,						1.0, 1.0, 1.0,		1.0, 1.0,
		(baseXPosition + sideBaseLenght + sideBaseLenght)* scale,(sideBaseHalfeHight)*scale,(-sideBaseWidth)* scale,						1.0, 1.0, 1.0,		1.0, 0.0,

		//rechteck rechts
		(baseXPosition + sideBaseLenght + sideBaseLenght)* scale,(sideBaseHalfeHight)*scale,(sideBaseWidth)*scale,		1.0, 1.0, 1.0,		1.0, 0.0,
		(baseXPosition + sideBaseLenght)*scale,(sideBaseHalfeHight)*scale,(sideBaseWidth)*scale,							1.0, 1.0, 1.0,		0.0, 0.0,
		(baseXPosition + sideBaseLenght)*scale,(sideBaseHight)*scale,(sideBaseWidth)*scale,							1.0, 1.0, 1.0,		0.0, 1.0,
		(baseXPosition + sideBaseLenght + sideBaseLenght)* scale,(sideBaseHight)*scale,(sideBaseWidth)*scale,		1.0, 1.0, 1.0,		1.0, 1.0,

		//rechteck links
		(baseXPosition + sideBaseLenght + sideBaseLenght)* scale,(sideBaseHight)*scale,(-sideBaseWidth)* scale,		1.0, 1.0, 1.0,		1.0, 1.0,
		(baseXPosition + sideBaseLenght)*scale,(sideBaseHight)*scale,(-sideBaseWidth)* scale,							1.0, 1.0, 1.0,		0.0, 1.0,
		(baseXPosition + sideBaseLenght)*scale,(sideBaseHalfeHight)*scale,(-sideBaseWidth)* scale,						1.0, 1.0, 1.0,		0.0, 0.0,
		(baseXPosition + sideBaseLenght + sideBaseLenght)* scale,(sideBaseHalfeHight)*scale,(-sideBaseWidth)* scale,		1.0, 1.0, 1.0,		1.0, 0.0,


	};

	unsigned int indices[] = {

		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20,

		24, 25, 26,
		26, 27, 24,

		28, 29, 30,

		31, 32, 33,

		34, 35, 36,

		37, 38, 39,

		40, 41, 42,
		42, 43, 40,

		44, 45, 46,
		46, 47, 44,





		48, 49, 50,
		50, 51, 48,
		
		52, 53, 54,
		54, 55, 52,

		56, 57, 58,
		58, 59, 56,

		60, 61, 62,
		62, 63, 60,

		64, 65, 66,
		66, 67, 64,

		68, 69, 70,
		70, 71, 68,

		72, 73, 74,
		74, 75, 72,

		76, 77, 78,

		79, 80, 81,

		82, 83, 84,

		85, 86, 87,

		88, 89, 90,
		90, 91, 88,

		92, 93, 94,
		94, 95, 92,
		

	};

	glGenVertexArrays(1, &baseVAO);
	glGenBuffers(1, &baseVBO);
	glGenBuffers(1, &baseEBO);

	//bind the VAO first, then bind and set vertex buffer(s), then config vertex attributes.
	glBindVertexArray(baseVAO);

	glBindBuffer(GL_ARRAY_BUFFER, baseVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, baseEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Rebelbase::redrawBase() {


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, BaseTexture);

	glBindVertexArray(baseVAO);
	glDrawElements(GL_TRIANGLES, 132, GL_UNSIGNED_INT, 0);	// 66 -> 132

}

void Rebelbase::drawBase() {

	glm::mat4 model = glm::mat4(1.0f);

	GLfloat zChange = 2.0f;

	redrawBase();

	model = glm::translate(model, glm::vec3(0, 0, zChange));
	baseShader.setMat4("model", model);
	redrawBase();

	model = glm::mat4(1.0f);
	baseShader.setMat4("model", model);

	model = glm::translate(model, glm::vec3(0, 0, -zChange));
	baseShader.setMat4("model", model);
	redrawBase();

}
