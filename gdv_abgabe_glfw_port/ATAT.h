#pragma once

#include <glad/glad.h>

#include "stb_image.h"
#include "Shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


#include <iostream>

class ATAT
{
public:

	// Shader
	Shader atatShader;

	//Body
	void drawBodySetup(GLfloat scale);

	//Head
	void drawHeadSetup(GLfloat scale);

	//========== 4 Beinstreben direkt am Körper ==========
	void drawLegSupportSetup(GLfloat scale);


	//========== 4 upper leg ==========
	void drawLFUpperLegSetup(GLfloat scale);

	void drawRFUpperLegSetup(GLfloat scale);

	void drawLRUpperLegSetup(GLfloat scale);

	void drawRRUpperLegSetup(GLfloat scale);
	//========== 4 lower leg ==========
	void drawLFLowerLegSetup(GLfloat scale);

	void drawRFLowerLegSetup(GLfloat scale);

	void drawLRLowerLegSetup(GLfloat scale);

	void drawRRLowerLegSetup(GLfloat scale);

	//==================== redraw ====================





	void redrawBody();

	void redrawUpperLeg();

	void loadTextures();





	//==================== initial draw ====================

	void initialDraw(glm::mat4 mView, glm::vec3 lightPos, glm::vec3 camPos);

	//body
	unsigned int testVBO;
	GLuint testVAO;
	unsigned int testEBO;

	//leg
	unsigned int legVBO;
	GLuint legVAO;
	unsigned int legEBO;

	unsigned int darkMetalTexture;


protected:
	/*


	C - z - B - z - A - Tunnel - Head


	*/


	//B - middle Section
	GLfloat bLength = 0.16f;
	GLfloat bLowerHight = 0.6f;
	GLfloat bUpperHight = 1.0f;
	GLfloat bUpperWidth = 0.12f;

	GLfloat bTiltMod = 0.03f;

	GLfloat bLowerWidth = bUpperWidth + bTiltMod;

	//z - slope connector
	GLfloat zLengthMod = 0.02f;
	GLfloat zHightMod = 0.05f;
	GLfloat zSlopeMod = 0.04f;

	GLfloat zLenth = bLength + zLengthMod;

	//C - back Section
	GLfloat cUpperLenth = 0.18f;
	GLfloat cLowerLenth = 0.23f;
	GLfloat cUpperHightMod = 0.05f;
	GLfloat cWidthMod = 0.02f;

	//========== legs ==========

	GLfloat upperLegHeight = bLowerHight - 0.05f;	//obere Höhe
	GLfloat kneeHeight = 0.275f;

	GLfloat lowerHeight = 0.0f;

	GLfloat comLegWidth = bLowerWidth / 4;
	GLfloat comLegLength = bLength / 3;

	GLfloat legWidth = comLegWidth;		//kurze Seite
	GLfloat legLength = comLegLength;	//lange seite

private:

};


