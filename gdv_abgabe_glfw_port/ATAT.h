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

	//Shader
	Shader atatShader;

	//========== setup ==========

	void drawBodySetup(GLfloat scale);
	void drawLegSetup(GLfloat scale);

	//Head ->maybe if we want to move the head independantly
	//void drawHeadSetup(GLfloat scale);

	//==================== redraw ====================
	void redrawATAT();
	void redrawBody();
	void redrawLeg();

	//==================== initial draw ====================

	void initialDraw(glm::mat4 mView, glm::vec3 lightPos, glm::vec3 camPos);
	void loadTextures();

	//body
	unsigned int testVBO;
	GLuint testVAO;
	unsigned int testEBO;

	//legs
	unsigned int legVBO;
	GLuint legVAO;
	unsigned int legEBO;

	//texture
	unsigned int darkMetalTexture;

	//==================== animation values ====================

	void animateBody(GLfloat velocity, GLfloat upperLegAngle);

	//0 vorne rechts
	//1 hinten rechts
	//2 vorne links
	//3 hinten links
	void animateLeg(glm::mat4 model, GLfloat x, GLfloat z, GLfloat upperLegAngle, GLfloat lowerAngle, GLfloat rotation, short type);

	//true for forward, false for bachward
	void changeAnimateValues();
	void changeRotation();

	GLfloat forwardMovementRLU = -24;
	GLfloat forwardMovementRLB = -8;
	GLfloat forwardMovementLUF = 8;
	GLfloat forwardMovementLUB = 24;

	GLfloat lowerLegMovRF = 0;
	GLfloat lowerLegMovRB = 0;
	GLfloat lowerLegMovLF = 0;
	GLfloat lowerLegMovLB = 0;

	//when leg moving forward -> true, else false;
	bool legStateRF = true;
	bool legStateRB = false;
	bool legStateLF = false;
	bool legStateLB = false;

	//speed of the atat and animation
	GLfloat speed = 0;

	//- right, + left
	GLfloat sidewardRotation = 0;

	//==================== helper ====================
	glm::vec3 calcNorm(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
	void calcSides(GLfloat& x, GLfloat& z, GLfloat speedMod, GLfloat rot);


protected:

	int scale = 2;

	/*
	C - z - B - z - A - Tunnel - Head
	*/

	GLfloat currentForward = 0;
	GLfloat currentAngle = 0;
	GLfloat currentX = 0;
	GLfloat currentZ = 0;

	//B - middle Section
	GLfloat bLength = 0.16f;
	GLfloat bLowerHight = 0.8f;
	GLfloat bUpperHight = 1.2f;
	GLfloat bUpperWidth = 0.12f;
	GLfloat bTiltMod = 0.03f;
	GLfloat bLowerWidth = bUpperWidth + bTiltMod;

	//z - slope connector
	GLfloat zLengthMod = 0.03f;
	GLfloat zHightMod = 0.05f;
	GLfloat zSlopeMod = 0.02f;
	GLfloat zLenth = bLength + zLengthMod;

	//C - back Section
	GLfloat cUpperLenth = 0.18f;
	GLfloat cLowerLenth = 0.23f;
	GLfloat cUpperHightMod = 0.05f;
	GLfloat cWidthMod = 0.02f;

	//legs
	GLfloat upperLegHeight = bLowerHight - 0.05f;	//upper hight
	GLfloat kneeHeight = 0.475f;
	GLfloat lowerHeight = 0.2f;
	GLfloat legWidth = bLowerWidth / 4;		//kurze Seite
	GLfloat legLength = bLength / 3;	//lange seite

	//========== neck ========== 0.8 max
	GLfloat neckwidthMod = 0.06f;		//bLowerWidth - zSlopeMod - cWidthMod - neckwidthMod -> 0.12+0.03 - 0.02 - 0.02 - 0.05 = 0.06
	GLfloat neckLength = 0.15f;
	GLfloat neckHight = 0.18f;
	GLfloat neckLowerHightMod = 0.02f;
	GLfloat neckMiddleWidth = 0.02f;


private:

};


