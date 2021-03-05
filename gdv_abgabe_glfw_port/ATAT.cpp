#include "ATAT.h"

ATAT::ATAT() {
	//speed and frames
	lastTime = glfwGetTime();
	lastFrameTime = lastTime;
}

glm::vec3 ATAT::calcNorm(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
	//aus 3 Punkten 2 Vectoren bilden, von diesen beiden das Kreuzprodukt bilden
	glm::vec3 u = p2 - p1;
	glm::vec3 v = p3 - p1;
	glm::vec3 normal = glm::cross(u, v);
	return normal;
}

void ATAT::calcSides(GLfloat& x, GLfloat& z, GLfloat speedMod, GLfloat rotation) {
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

void ATAT::drawBodySetup(GLfloat scale) {
	float vertices[] = {
		// positions                                                                    colors                  texture coord

	//========== mittelteil ==========

	//mittlere unterseite
	bLength * scale, bLowerHight * scale, (-bLowerWidth) * scale,          1.0f, 1.0f, 1.0f,      1.0f, 1.0f,     // top right        0
	bLength * scale,  bLowerHight * scale, (bLowerWidth)*scale,             1.0f, 1.0f, 1.0f,     1.0f, 0.0f,     // bottom right     1
	(-bLength) * scale,  bLowerHight * scale, (bLowerWidth)*scale,         1.0f, 1.0f, 1.0f,     0.0f, 0.0f,     // bottom left      2
	(-bLength) * scale, bLowerHight * scale, (-bLowerWidth) * scale,          1.0f, 1.0f, 1.0f,    0.0f, 1.0f,     // top left         3

	//mittlere linke Seite
	(-bLength) * scale,  bUpperHight * scale, (-bUpperWidth) * scale,      1.0f, 1.0f, 1.0f,       0.0f, 1.0f,      // top left        7
	(-bLength) * scale, bLowerHight * scale, (-bLowerWidth) * scale,       1.0f, 1.0f, 1.0f,       0.0f, 0.0f,     // bottom left      6
	bLength * scale, bLowerHight * scale, (-bLowerWidth) * scale,         1.0f, 1.0f, 1.0f,       1.0f, 0.0f,     //bottom right      5
	 bLength * scale, bUpperHight * scale, (-bUpperWidth) * scale,         1.0f, 1.0f, 1.0f,       1.0f, 1.0f,     // top right        4

	///rechte mittlere Seite
	 bLength * scale, bUpperHight * scale, bUpperWidth * scale,            1.0f, 1.0f, 1.0f,       1.0f, 1.0f,     // top right        8
	 bLength * scale, bLowerHight * scale, (bLowerWidth)*scale,           1.0f, 1.0f, 1.0f,       1.0f, 0.0f,     //bottom right      9                                           // bottom right
	(-bLength) * scale, bLowerHight * scale, (bLowerWidth)*scale,        1.0f, 1.0f, 1.0f,       0.0f, 0.0f,     // bottom left      10
	(-bLength) * scale,  bUpperHight * scale, bUpperWidth * scale,         1.0f, 1.0f, 1.0f,       0.0f, 1.0f,     // top left         11

	//mittlere oberseite

	(-bLength) * scale, bUpperHight * scale, (-bUpperWidth) * scale,		1.0f, 1.0f, 1.0f,       0.0f, 1.0f,     //                  15
	(-bLength) * scale,  bUpperHight * scale, bUpperWidth * scale,				1.0f, 1.0f, 1.0f,       0.0f, 0.0f,     //                  14
	bLength * scale,  bUpperHight * scale, bUpperWidth * scale,				1.0f, 1.0f, 1.0f,       1.0f, 0.0f,     // top left         13
	bLength * scale, bUpperHight * scale, (-bUpperWidth) * scale,				1.0f, 1.0f, 1.0f,       1.0f, 1.0f,     //                  12

	//========== schr?gen hinten ==========

	//linke schr?gseite
	(-bLength - zLengthMod) * scale,  (bUpperHight - zHightMod) * scale, (-bUpperWidth + zSlopeMod) * scale,    1.0f, 1.0f, 1.0f,       0.0f, 1.0f,     // 19 top right
	(-bLength - zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod) * scale,                  1.0f, 1.0f, 1.0f,       0.0f, 0.0f,     // 18 bottom
	(-bLength) * scale, bLowerHight * scale, (-bLowerWidth) * scale,                                           1.0f, 1.0f, 1.0f,       1.0f, 0.0f,     // 17 bottom left
	(-bLength) * scale,  bUpperHight * scale, (-bUpperWidth) * scale,                                           1.0f, 1.0f, 1.0f,       1.0f, 1.0f,     // 16 top right

	//untere Schr?gseite
	(-bLength) * scale,  bLowerHight * scale, (-bLowerWidth) * scale,                                          1.0f, 1.0f, 1.0f,       1.0f, 1.0f,     // 20 top right
	(-bLength) * scale, bLowerHight * scale, (bLowerWidth)*scale,                                            1.0f, 1.0f, 1.0f,       1.0f, 0.0f,     // 21 bottom left
	(-bLength - zLengthMod) * scale,  bLowerHight * scale, (bLowerWidth - zSlopeMod) * scale,                  1.0f, 1.0f, 1.0f,       0.0f, 0.0f,     // 22 top right
	(-bLength - zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod) * scale,                  1.0f, 1.0f, 1.0f,       0.0f, 1.0f,     // 23 bottom left

	//rechte schr?gseite
	(-bLength) * scale,  bUpperHight * scale, (bUpperWidth)*scale,                                           1.0f, 1.0f, 1.0f,       1.0f, 1.0f,     // 24 top right
	(-bLength) * scale, bLowerHight * scale, (bLowerWidth)*scale,                                            1.0f, 1.0f, 1.0f,       1.0f, 0.0f,     // 25 bottom left
	(-bLength - zLengthMod) * scale, bLowerHight * scale, (bLowerWidth - zSlopeMod) * scale,                   1.0f, 1.0f, 1.0f,       0.0f, 0.0f,     // 26 bottom
	(-bLength - zLengthMod) * scale,  (bUpperHight - zHightMod) * scale, (bUpperWidth - zSlopeMod) * scale,    1.0f, 1.0f, 1.0f,       0.0f, 1.0f,     // 27 top right

	//obere Schr?gseite
	(-bLength) * scale,  bUpperHight * scale, (-bUpperWidth) * scale,                                         1.0f, 1.0f, 1.0f,       1.0f, 1.0f,     // 28 top right
	(-bLength) * scale, bUpperHight * scale, (bUpperWidth)*scale,                                            1.0f, 1.0f, 1.0f,       1.0f, 0.0f,     // 29 bottom left
	(-bLength - zLengthMod) * scale,  (bUpperHight - zHightMod) * scale, (bUpperWidth - zSlopeMod) * scale,    1.0f, 1.0f, 1.0f,       0.0f, 0.0f,     // 30 top right
	(-bLength - zLengthMod) * scale, (bUpperHight - zHightMod) * scale, (-bUpperWidth + zSlopeMod) * scale,    1.0f, 1.0f, 1.0f,       0.0f, 1.0f,     // 31 bottom left

	//========== hintere Seiten ==========

	//unterseite
	(-bLength - zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod) * scale,                              1.0f, 1.0f, 1.0f,       1.0f, 1.0f,     // 32 bottom left
	(-bLength - zLengthMod) * scale,  bLowerHight * scale, (bLowerWidth - zSlopeMod) * scale,                              1.0f, 1.0f, 1.0f,       1.0f, 0.0f,     // 33 top right
	(-cLowerLenth - bLength - zLengthMod) * scale, bLowerHight * scale, (bLowerWidth - zSlopeMod - cWidthMod) * scale,        1.0f, 1.0f, 1.0f,       0.0f, 0.0f, //34
	(-cLowerLenth - bLength - zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod + cWidthMod) * scale,    1.0f, 1.0f, 1.0f,       0.0f, 1.0f, //35

	//linke seite
	(-cUpperLenth - bLength - zLengthMod) * scale, (bUpperHight - zHightMod - cUpperHightMod) * scale, (-bLowerWidth + zSlopeMod + cWidthMod) * scale,     1.0f, 1.0f, 1.0f,       0.0f, 1.0f, //39
	(-cLowerLenth - bLength - zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod + cWidthMod) * scale,                                    1.0f, 1.0f, 1.0f,       0.0f, 0.0f, //38
	(-bLength - zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod) * scale,                                                              1.0f, 1.0f, 1.0f,       1.0f, 0.0f, // 37 bottom left
	(-bLength - zLengthMod) * scale,  (bUpperHight - zHightMod) * scale, (-bUpperWidth + zSlopeMod) * scale,                                               1.0f, 1.0f, 1.0f,       1.0f, 1.0f, // 36 bottom left

	//oberseite
	(-bLength - zLengthMod) * scale, (bUpperHight - zHightMod) * scale, (-bUpperWidth + zSlopeMod) * scale,                                                1.0f, 1.0f, 1.0f,       1.0f, 1.0f,     // 40 bottom left
	(-bLength - zLengthMod) * scale,  (bUpperHight - zHightMod) * scale, (bUpperWidth - zSlopeMod) * scale,                                                1.0f, 1.0f, 1.0f,       1.0f, 0.0f,     // 41 top right
	(-cUpperLenth - bLength - zLengthMod) * scale, (bUpperHight - zHightMod - cUpperHightMod) * scale, (bLowerWidth - zSlopeMod - cWidthMod) * scale,      1.0f, 1.0f, 1.0f,       0.0f, 0.0f, //42
	(-cUpperLenth - bLength - zLengthMod) * scale, (bUpperHight - zHightMod - cUpperHightMod) * scale, (-bLowerWidth + zSlopeMod + cWidthMod) * scale,     1.0f, 1.0f, 1.0f,       0.0f, 1.0f, //43

	//rechte Seite
	(-bLength - zLengthMod) * scale,  (bUpperHight - zHightMod) * scale, (bUpperWidth - zSlopeMod) * scale,                                               1.0f, 1.0f, 1.0f,       0.0f, 1.0f, // 44 bottom left
	(-bLength - zLengthMod) * scale, bLowerHight * scale, (bLowerWidth - zSlopeMod) * scale,                                                              1.0f, 1.0f, 1.0f,       0.0f, 0.0f, // 45 bottom left
	(-cLowerLenth - bLength - zLengthMod) * scale, bLowerHight * scale, (bLowerWidth - zSlopeMod - cWidthMod) * scale,                                    1.0f, 1.0f, 1.0f,       1.0f, 0.0f, //46
	(-cUpperLenth - bLength - zLengthMod) * scale, (bUpperHight - zHightMod - cUpperHightMod) * scale, (bLowerWidth - zSlopeMod - cWidthMod) * scale,     1.0f, 1.0f, 1.0f,       1.0f, 1.0f, //47

	//hintere Seite
	(-cUpperLenth - bLength - zLengthMod) * scale, (bUpperHight - zHightMod - cUpperHightMod) * scale, (-bLowerWidth + zSlopeMod + cWidthMod) * scale,     1.0f, 1.0f, 1.0f,       1.0f, 1.0f, //48
	(-cUpperLenth - bLength - zLengthMod) * scale, (bUpperHight - zHightMod - cUpperHightMod) * scale, (bLowerWidth - zSlopeMod - cWidthMod) * scale,      1.0f, 1.0f, 1.0f,       1.0f, 0.0f, //49
	(-cLowerLenth - bLength - zLengthMod) * scale, bLowerHight * scale, (bLowerWidth - zSlopeMod - cWidthMod) * scale,                                     1.0f, 1.0f, 1.0f,       0.0f, 0.0f, //50
	(-cLowerLenth - bLength - zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod + cWidthMod) * scale,                                    1.0f, 1.0f, 1.0f,       0.0f, 1.0f, //51

	//========== schrägen vorne ==========

	 //linke schr?gseite
	(bLength)*scale,  bUpperHight * scale, (-bUpperWidth) * scale,                                           1.0f, 1.0f, 1.0f,       0.2f, 1.0f,     // 52 top right
	(bLength)*scale, bLowerHight * scale, (-bLowerWidth) * scale,                                            1.0f, 1.0f, 1.0f,       0.2f, 0.0f,     // 53 bottom left
	(bLength + zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod) * scale,                   1.0f, 1.0f, 1.0f,       0.0f, 0.0f,     // 54 bottom
	(bLength + zLengthMod) * scale,  (bUpperHight - zHightMod) * scale, (-bUpperWidth + zSlopeMod) * scale,    1.0f, 1.0f, 1.0f,       0.0f, 1.0f,     // 55 top right

	//untere Schr?gseite
	(bLength + zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod) * scale,                   1.0f, 1.0f, 1.0f,       0.0f, 1.0f,     // 59 bottom left
	(bLength + zLengthMod) * scale, bLowerHight * scale, (bLowerWidth - zSlopeMod) * scale, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,     // 58 top right
	(bLength)*scale, bLowerHight * scale, (bLowerWidth)*scale, 1.0f, 1.0f, 1.0f, 0.2f, 0.0f,     // 57 bottom left
	(bLength)*scale, bLowerHight * scale, (-bLowerWidth) * scale, 1.0f, 1.0f, 1.0f, 0.2f, 1.0f,     // 56 top right

	//rechte schr?gseite
	(bLength + zLengthMod) * scale,  (bUpperHight - zHightMod) * scale, (bUpperWidth - zSlopeMod) * scale,     1.0f, 1.0f, 1.0f,    0.0f, 1.0f,     // 63 top right
	(bLength + zLengthMod) * scale, bLowerHight * scale, (bLowerWidth - zSlopeMod) * scale, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,     // 62 bottom
	(bLength)*scale, bLowerHight * scale, (bLowerWidth)*scale, 1.0f, 1.0f, 1.0f, 0.2f, 0.0f,     // 61 bottom left
	(bLength)*scale, bUpperHight * scale, (bUpperWidth)*scale, 1.0f, 1.0f, 1.0f, 0.2f, 1.0f,     // 60 top right

	//obere Schr?gseite
	(bLength + zLengthMod) * scale, (bUpperHight - zHightMod) * scale, (-bUpperWidth + zSlopeMod) * scale,         1.0f, 1.0f, 1.0f,       0.5f, 0.0f,     // 67 bottom left
	(bLength + zLengthMod) * scale, (bUpperHight - zHightMod) * scale, (bUpperWidth - zSlopeMod) * scale, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,     // 66 top right
	(bLength)*scale, bUpperHight * scale, (bUpperWidth)*scale, 1.0f, 1.0f, 1.0f, 0.0f, 0.3f,     // 65 bottom left
	(bLength)*scale, bUpperHight * scale, (-bUpperWidth) * scale, 1.0f, 1.0f, 1.0f, 0.5f, 0.3f,     // 64 top right

	//========== vordere Seiten ==========

	//unterseite
	(cUpperLenth + bLength + zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod + cWidthMod) * scale, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, //71
	(cUpperLenth + bLength + zLengthMod) * scale, bLowerHight * scale, (bLowerWidth - zSlopeMod - cWidthMod) * scale, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //70
	(bLength + zLengthMod) * scale, bLowerHight * scale, (bLowerWidth - zSlopeMod) * scale, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,     // 69 top right
	(bLength + zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod) * scale, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,     // 68 bottom left

	//linke seite
	(bLength + zLengthMod) * scale, (bUpperHight - zHightMod) * scale, (-bUpperWidth + zSlopeMod) * scale, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // 72 bottom left
	(bLength + zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod) * scale, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // 73 bottom left
	(cUpperLenth + bLength + zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod + cWidthMod) * scale, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //74
	(cUpperLenth + bLength + zLengthMod) * scale, (bUpperHight - zHightMod - cUpperHightMod) * scale, (-bLowerWidth + zSlopeMod + cWidthMod) * scale, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, //75

	//oberseite
	(bLength + zLengthMod) * scale, (bUpperHight - zHightMod) * scale, (-bUpperWidth + zSlopeMod) * scale, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,     // 76 bottom left
	(bLength + zLengthMod) * scale, (bUpperHight - zHightMod) * scale, (bUpperWidth - zSlopeMod) * scale, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,     // 77 top right
	(cUpperLenth + bLength + zLengthMod) * scale, (bUpperHight - zHightMod - cUpperHightMod) * scale, (bLowerWidth - zSlopeMod - cWidthMod) * scale, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //78
	(cUpperLenth + bLength + zLengthMod) * scale, (bUpperHight - zHightMod - cUpperHightMod) * scale, (-bLowerWidth + zSlopeMod + cWidthMod) * scale, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, //79

	//rechte Seite
	(cUpperLenth + bLength + zLengthMod) * scale, (bUpperHight - zHightMod - cUpperHightMod) * scale, (bLowerWidth - zSlopeMod - cWidthMod) * scale,	1.0f, 1.0f, 1.0f,	1.0f, 1.0f, //83 oben rechts
	(cUpperLenth + bLength + zLengthMod) * scale, bLowerHight * scale, (bLowerWidth - zSlopeMod - cWidthMod) * scale,										1.0f, 1.0f, 1.0f,	1.0f, 0.0f, //82 unten rechts
	(bLength + zLengthMod) * scale, bLowerHight * scale, (bLowerWidth - zSlopeMod) * scale,																1.0f, 1.0f, 1.0f,	0.0f, 0.0f, // 81 unten left
	(bLength + zLengthMod) * scale, (bUpperHight - zHightMod) * scale, (bUpperWidth - zSlopeMod) * scale,													1.0f, 1.0f, 1.0f,	0.0f, 1.0f, // oben links

	//hintere Seite
	(cUpperLenth + bLength + zLengthMod) * scale, bLowerHight * scale, (-bLowerWidth + zSlopeMod + cWidthMod) * scale, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, //87
	(cUpperLenth + bLength + zLengthMod) * scale, bLowerHight * scale, (bLowerWidth - zSlopeMod - cWidthMod) * scale, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //86
	(cUpperLenth + bLength + zLengthMod) * scale, (bUpperHight - zHightMod - cUpperHightMod) * scale, (bLowerWidth - zSlopeMod - cWidthMod) * scale, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //85
	(cUpperLenth + bLength + zLengthMod) * scale, (bUpperHight - zHightMod - cUpperHightMod) * scale, (-bLowerWidth + zSlopeMod + cWidthMod) * scale, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //84

	//========== neck ==========

	//unterseite
	(cUpperLenth + bLength + zLengthMod + neckLength) * scale, (bLowerHight + neckLowerHightMod) * scale, (-neckwidthMod) * scale, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //90
	(cUpperLenth + bLength + zLengthMod + neckLength) * scale, (bLowerHight + neckLowerHightMod) * scale, (neckwidthMod)*scale, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //91
	(cUpperLenth + bLength + zLengthMod) * scale, (bLowerHight + neckLowerHightMod) * scale, (neckwidthMod)*scale, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, //89
	(cUpperLenth + bLength + zLengthMod) * scale, (bLowerHight + neckLowerHightMod) * scale, (-neckwidthMod) * scale, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //88

	//oberseite
	(cUpperLenth + bLength + zLengthMod + neckLength) * scale, ((bLowerHight + neckLowerHightMod) + neckHight) * scale, (-neckwidthMod) * scale,	1.0f, 1.0f, 1.0f,	0.0f, 1.0f, //92
	(cUpperLenth + bLength + zLengthMod) * scale, ((bLowerHight + neckLowerHightMod) + neckHight) * scale, (-neckwidthMod) * scale,				1.0f, 1.0f, 1.0f,	0.0f, 0.0f, //95
	(cUpperLenth + bLength + zLengthMod) * scale, ((bLowerHight + neckLowerHightMod) + neckHight) * scale, (neckwidthMod)*scale,					1.0f, 1.0f, 1.0f,	1.0f, 0.0f, //94
	(cUpperLenth + bLength + zLengthMod + neckLength) * scale, ((bLowerHight + neckLowerHightMod) + neckHight) * scale, (neckwidthMod)*scale,		1.0f, 1.0f, 1.0f,	1.0f, 1.0f, //93

	//rechts oben
	(cUpperLenth + bLength + zLengthMod + neckLength) * scale, ((bLowerHight + neckLowerHightMod) + (neckHight)) * scale, (neckwidthMod)*scale, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //96
	(cUpperLenth + bLength + zLengthMod + neckLength) * scale, ((bLowerHight + neckLowerHightMod) + (neckHight / 2)) * scale, (neckwidthMod + neckMiddleWidth) * scale, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //97
	(cUpperLenth + bLength + zLengthMod) * scale, ((bLowerHight + neckLowerHightMod) + (neckHight / 2)) * scale, (neckwidthMod + neckMiddleWidth) * scale, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //98
	(cUpperLenth + bLength + zLengthMod) * scale, ((bLowerHight + neckLowerHightMod) + neckHight) * scale, (neckwidthMod)*scale, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, //99

	//rechts unten
	(cUpperLenth + bLength + zLengthMod + neckLength) * scale, ((bLowerHight + neckLowerHightMod) + (neckHight / 2)) * scale, (neckwidthMod + neckMiddleWidth) * scale, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //100
	(cUpperLenth + bLength + zLengthMod + neckLength) * scale, (bLowerHight + neckLowerHightMod) * scale, (neckwidthMod)*scale, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //101
	(cUpperLenth + bLength + zLengthMod) * scale, (bLowerHight + neckLowerHightMod) * scale, (neckwidthMod)*scale, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, //102
	(cUpperLenth + bLength + zLengthMod) * scale, ((bLowerHight + neckLowerHightMod) + (neckHight / 2)) * scale, (neckwidthMod + neckMiddleWidth) * scale, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //103

	//links oben
	(cUpperLenth + bLength + zLengthMod + neckLength) * scale, ((bLowerHight + neckLowerHightMod) + (neckHight)) * scale, (-neckwidthMod) * scale,								1.0f, 1.0f, 1.0f,	0.0f, 1.0f, //104
	(cUpperLenth + bLength + zLengthMod) * scale, ((bLowerHight + neckLowerHightMod) + neckHight) * scale, (-neckwidthMod) * scale,											1.0f, 1.0f, 1.0f,	1.0f, 1.0f, //107
	(cUpperLenth + bLength + zLengthMod) * scale, ((bLowerHight + neckLowerHightMod) + (neckHight / 2)) * scale, (-neckwidthMod - neckMiddleWidth) * scale,					1.0f, 1.0f, 1.0f,	1.0f, 0.0f, //106
	(cUpperLenth + bLength + zLengthMod + neckLength) * scale, ((bLowerHight + neckLowerHightMod) + (neckHight / 2)) * scale, (-neckwidthMod - neckMiddleWidth) * scale,		1.0f, 1.0f, 1.0f,	0.0f, 0.0f, //105

	//links unten
	(cUpperLenth + bLength + zLengthMod + neckLength) * scale, (bLowerHight + neckLowerHightMod) * scale, (-neckwidthMod) * scale,												1.0f, 1.0f, 1.0f,	0.0f, 1.0f, //109
	(cUpperLenth + bLength + zLengthMod + neckLength) * scale, ((bLowerHight + neckLowerHightMod) + (neckHight / 2)) * scale, (-neckwidthMod - neckMiddleWidth) * scale,		1.0f, 1.0f, 1.0f,	0.0f, 0.0f, //108
	(cUpperLenth + bLength + zLengthMod) * scale, ((bLowerHight + neckLowerHightMod) + (neckHight / 2)) * scale, (-neckwidthMod - neckMiddleWidth) * scale,					1.0f, 1.0f, 1.0f,	1.0f, 0.0f, //111
	(cUpperLenth + bLength + zLengthMod) * scale, (bLowerHight + neckLowerHightMod) * scale, (-neckwidthMod) * scale,															1.0f, 1.0f, 1.0f,	1.0f, 1.0f, //110

	//========== Head ==========

	//hinterseite
	(headBackSidePos)*scale, (headHight)*scale, (headUpperWidth)*scale,												1.0f, 1.0f, 1.0f,	0.0f, 1.0f, //112
	(headBackSidePos)*scale, (bLowerHight + neckLowerHightMod - headLowerBackHight) * scale, (headLowerWidth)*scale,	1.0f, 1.0f, 1.0f,	0.0f, 0.0f, //113
	(headBackSidePos)*scale, (bLowerHight + neckLowerHightMod - headLowerBackHight) * scale, (-headLowerWidth) * scale,	1.0f, 1.0f, 1.0f,	1.0f, 0.0f, //114
	(headBackSidePos)*scale, (headHight)*scale, (-headUpperWidth) * scale,												1.0f, 1.0f, 1.0f,	1.0f, 1.0f, //115

	//unterseite
	(headBackSidePos)*scale, (bLowerHight + neckLowerHightMod - headLowerBackHight) * scale, (-headLowerWidth) * scale,										1.0f, 1.0f, 1.0f,	1.0f, 1.0f, //119
	(headBackSidePos + headLowerLength) * scale, (bLowerHight + neckLowerHightMod - headLowerBackHight) * scale, (-headLowerWidth + headFLWidth) * scale, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //118
	(headBackSidePos + headLowerLength) * scale, (bLowerHight + neckLowerHightMod - headLowerBackHight) * scale, (headLowerWidth - headFLWidth) * scale, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //117
	(headBackSidePos)*scale, (bLowerHight + neckLowerHightMod - headLowerBackHight) * scale, (headLowerWidth)*scale, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, //116

	//oberseite
	(headBackSidePos)*scale, (headHight)*scale, (headUpperWidth)*scale,																				1.0f, 1.0f, 1.0f, 0.0f, 1.0f, //120
	(headBackSidePos + headLowerLength - upperSLopeLengthMod) * scale, (headHight - upperSlopeMod) * scale, (headLowerWidth - headFLWidth) * scale,			1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //121
	(headBackSidePos + headLowerLength - upperSLopeLengthMod) * scale, (headHight - upperSlopeMod) * scale, (-headLowerWidth + headFLWidth) * scale,		1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //122
	(headBackSidePos)*scale, (headHight)*scale, (-headUpperWidth) * scale,																				1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //123

	//frontside
	(headBackSidePos + headLowerLength - upperSLopeLengthMod) * scale, (headHight - upperSlopeMod) * scale, (-headLowerWidth + headFLWidth) * scale,			1.0f, 1.0f, 1.0f,	0.0f, 1.0f, //127
	(headBackSidePos + headLowerLength) * scale, (bLowerHight + neckLowerHightMod - headLowerBackHight) * scale, (-headLowerWidth + headFLWidth) * scale, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //125
	(headBackSidePos + headLowerLength) * scale, (bLowerHight + neckLowerHightMod - headLowerBackHight) * scale, (headLowerWidth - headFLWidth) * scale, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //126
	(headBackSidePos + headLowerLength - upperSLopeLengthMod) * scale, (headHight - upperSlopeMod) * scale, (headLowerWidth - headFLWidth) * scale, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //124

	//left side
	(headBackSidePos)*scale, (headHight)*scale, (-headUpperWidth) * scale,																					1.0f, 1.0f, 1.0f,	1.0f, 1.0f, //123
	(headBackSidePos)*scale, (bLowerHight + neckLowerHightMod - headLowerBackHight) * scale, (-headLowerWidth) * scale,										1.0f, 1.0f, 1.0f,	1.0f, 0.0f, //119
	(headBackSidePos + headLowerLength) * scale, (bLowerHight + neckLowerHightMod - headLowerBackHight) * scale, (-headLowerWidth + headFLWidth) * scale,	1.0f, 1.0f, 1.0f,	0.0f, 0.0f, //125
	(headBackSidePos + headLowerLength - upperSLopeLengthMod) * scale, (headHight - upperSlopeMod) * scale, (-headLowerWidth + headFLWidth) * scale,		1.0f, 1.0f, 1.0f,	0.0f, 1.0f, //127

	//right side
	(headBackSidePos + headLowerLength - upperSLopeLengthMod) * scale, (headHight - upperSlopeMod) * scale, (headLowerWidth - headFLWidth) * scale,			1.0f, 1.0f, 1.0f,	1.0f, 1.0f, //127
	(headBackSidePos + headLowerLength) * scale, (bLowerHight + neckLowerHightMod - headLowerBackHight) * scale, (headLowerWidth - headFLWidth) * scale,	1.0f, 1.0f, 1.0f,	1.0f, 0.0f, //125
	(headBackSidePos)*scale, (bLowerHight + neckLowerHightMod - headLowerBackHight) * scale, (headLowerWidth)*scale,										1.0f, 1.0f, 1.0f,	0.0f, 0.0f, //119
	(headBackSidePos)*scale, (headHight)*scale, (headUpperWidth)*scale,																						1.0f, 1.0f, 1.0f,	0.0f, 1.0f, //123
	

	//===== cockpit =====
	
	//oben
	(headBackSidePos + headLowerLength - upperSLopeLengthMod)* scale, (headHight - upperSlopeMod - 0.03)* scale, (headLowerWidth - headFLWidth)* scale, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //124
	(headBackSidePos + headLowerLength + 0.025)* scale, (headHight - upperSlopeMod - 0.07)* scale, (headLowerWidth - headFLWidth - 0.04)* scale, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //126
	(headBackSidePos + headLowerLength + 0.025)* scale, (headHight - upperSlopeMod - 0.07)* scale, (-headLowerWidth + headFLWidth + 0.04)* scale, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //125
	(headBackSidePos + headLowerLength - upperSLopeLengthMod)* scale, (headHight - upperSlopeMod - 0.03)* scale, (-headLowerWidth + headFLWidth)* scale, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, //127

	//unten
	(headBackSidePos + headLowerLength - upperSLopeLengthMod)* scale, (headHight - upperSlopeMod - 0.12)* scale, (headLowerWidth - headFLWidth)* scale, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //124
	(headBackSidePos + headLowerLength + 0.025)* scale, (headHight - upperSlopeMod - 0.1)* scale, (headLowerWidth - headFLWidth - 0.04)* scale, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //126
	(headBackSidePos + headLowerLength + 0.025)* scale, (headHight - upperSlopeMod - 0.1)* scale, (-headLowerWidth + headFLWidth + 0.04)* scale, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //125
	(headBackSidePos + headLowerLength - upperSLopeLengthMod)* scale, (headHight - upperSlopeMod - 0.12)* scale, (-headLowerWidth + headFLWidth)* scale, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, //127

	//trapez rechts
	(headBackSidePos + headLowerLength + 0.025)* scale, (headHight - upperSlopeMod - 0.07)* scale, (headLowerWidth - headFLWidth - 0.04)* scale,			1.0f, 1.0f, 1.0f,	1.0f, 1.0f, //126
	(headBackSidePos + headLowerLength + 0.025)* scale, (headHight - upperSlopeMod - 0.1)* scale, (headLowerWidth - headFLWidth - 0.04)* scale,				1.0f, 1.0f, 1.0f,	1.0f, 0.0f, //126
	(headBackSidePos + headLowerLength - upperSLopeLengthMod)* scale, (headHight - upperSlopeMod - 0.12)* scale, (headLowerWidth - headFLWidth)* scale,		1.0f, 1.0f, 1.0f,	0.0f, 0.0f, //124
	(headBackSidePos + headLowerLength - upperSLopeLengthMod)* scale, (headHight - upperSlopeMod - 0.03)* scale, (headLowerWidth - headFLWidth)* scale,		1.0f, 1.0f, 1.0f,	0.0f, 1.0f, //124

	//trapez links
	(headBackSidePos + headLowerLength - upperSLopeLengthMod)* scale, (headHight - upperSlopeMod - 0.03)* scale, (-headLowerWidth + headFLWidth)* scale, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, //124
	(headBackSidePos + headLowerLength - upperSLopeLengthMod)* scale, (headHight - upperSlopeMod - 0.12)* scale, (-headLowerWidth + headFLWidth)* scale, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //124
	(headBackSidePos + headLowerLength + 0.025)* scale, (headHight - upperSlopeMod - 0.1)* scale, (-headLowerWidth + headFLWidth + 0.04)* scale, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //126
	(headBackSidePos + headLowerLength + 0.025)* scale, (headHight - upperSlopeMod - 0.07)* scale, (-headLowerWidth + headFLWidth + 0.04)* scale, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //126

	//front
	(headBackSidePos + headLowerLength + 0.025)* scale, (headHight - upperSlopeMod - 0.1)* scale, (-headLowerWidth + headFLWidth + 0.04)* scale,			1.0f, 1.0f, 1.0f,	0.0f, 1.0f, //125
	(headBackSidePos + headLowerLength + 0.025)* scale, (headHight - upperSlopeMod - 0.1)* scale, (headLowerWidth - headFLWidth - 0.04)* scale, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //126
	(headBackSidePos + headLowerLength + 0.025)* scale, (headHight - upperSlopeMod - 0.07)* scale, (headLowerWidth - headFLWidth - 0.04)* scale, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //126
	(headBackSidePos + headLowerLength + 0.025)* scale, (headHight - upperSlopeMod - 0.07)* scale, (-headLowerWidth + headFLWidth + 0.04)* scale, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //125


	//===== weaponrack =====

	//underside
	(headBackSidePos + 0.05)* scale, ((bLowerHight + neckLowerHightMod - headLowerBackHight))* scale, (-headLowerWidth + headFLWidth)* scale,											1.0f, 1.0f, 1.0f,	0.0f, 1.0f, //121
	(headBackSidePos + 0.05)* scale, ((bLowerHight + neckLowerHightMod - headLowerBackHight))* scale, (headLowerWidth - headFLWidth)* scale, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //121
	(headBackSidePos + headLowerLength - upperSLopeLengthMod)* scale, ((bLowerHight + neckLowerHightMod - headLowerBackHight - 0.04))* scale, (headLowerWidth - headFLWidth)* scale, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //121
	(headBackSidePos + headLowerLength - upperSLopeLengthMod)* scale, ((bLowerHight + neckLowerHightMod - headLowerBackHight - 0.04))* scale, (-headLowerWidth + headFLWidth)* scale, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //121

	//front
	(headBackSidePos + headLowerLength - upperSLopeLengthMod)* scale, ((bLowerHight + neckLowerHightMod - headLowerBackHight))* scale, (headLowerWidth - headFLWidth)* scale,			1.0f, 1.0f, 1.0f,	0.0f, 1.0f, //121
	(headBackSidePos + headLowerLength - upperSLopeLengthMod)* scale, ((bLowerHight + neckLowerHightMod - headLowerBackHight))* scale, (-headLowerWidth + headFLWidth)* scale, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //121
	(headBackSidePos + headLowerLength - upperSLopeLengthMod)* scale, ((bLowerHight + neckLowerHightMod - headLowerBackHight - 0.04))* scale, (-headLowerWidth + headFLWidth)* scale, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //121
	(headBackSidePos + headLowerLength - upperSLopeLengthMod)* scale, ((bLowerHight + neckLowerHightMod - headLowerBackHight - 0.04))* scale, (headLowerWidth - headFLWidth)* scale, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //121

	//right sides
	(headBackSidePos + 0.05)* scale, ((bLowerHight + neckLowerHightMod - headLowerBackHight))* scale, (headLowerWidth - headFLWidth)* scale,											1.0f, 1.0f, 1.0f,	0.0f, 0.0f, //121
	(headBackSidePos + headLowerLength - upperSLopeLengthMod)* scale, ((bLowerHight + neckLowerHightMod - headLowerBackHight))* scale, (headLowerWidth - headFLWidth)* scale, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, //121
	(headBackSidePos + headLowerLength - upperSLopeLengthMod)* scale, ((bLowerHight + neckLowerHightMod - headLowerBackHight - 0.04))* scale, (headLowerWidth - headFLWidth)* scale, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //121

	//left
	(headBackSidePos + headLowerLength - upperSLopeLengthMod)* scale, ((bLowerHight + neckLowerHightMod - headLowerBackHight - 0.04))* scale, (-headLowerWidth + headFLWidth)* scale, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //121
	(headBackSidePos + headLowerLength - upperSLopeLengthMod)* scale, ((bLowerHight + neckLowerHightMod - headLowerBackHight))* scale, (-headLowerWidth + headFLWidth)* scale, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, //121
	(headBackSidePos + 0.05)* scale, ((bLowerHight + neckLowerHightMod - headLowerBackHight))* scale, (-headLowerWidth + headFLWidth)* scale, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //121



};
	unsigned int indices[] = {  // note that we start from 0!
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
		30, 31, 28,

		32, 33, 34,
		34, 35, 32,

		36, 37, 38,
		38, 39, 36,

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
		78, 79, 76,

		80, 81, 82,
		82, 83, 80,

		84, 85, 86,
		86, 87, 84,

		88, 89, 90,
		90, 91, 88,

		92, 93, 94,
		94, 95, 92,

		96, 97, 98,
		98, 99, 96,

		100, 101, 102,
		102, 103, 100,

		104, 105, 106,
		106, 107, 104,

		108, 109, 110,
		110, 111, 108,

		112, 113, 114,
		114, 115, 112,

		116, 117, 118,
		118, 119, 116,

		120, 121, 122,
		122, 123, 120,

		124, 125, 126,
		126, 127, 124,

		128, 129, 130,
		130, 131, 128,

		132, 133, 134,
		134, 135, 132,

		136, 137, 138,
		138, 139, 136,

		140, 141, 142,
		142, 143, 140,

		144, 145, 146,
		146, 147, 144,

		148, 149, 150,
		150, 151, 148,

		152, 153, 154,
		154, 155, 152,

		156, 157, 158,
		158, 159, 156,

		160, 161, 162,
		162, 163, 160,

		164, 165, 166,

		167, 168, 169,

	};

	glGenVertexArrays(1, &testVAO);
	glGenBuffers(1, &testVBO);
	glGenBuffers(1, &testEBO);

	//bind the VAO first, then bind and set vertex buffer(s), then config vertex attributes.
	glBindVertexArray(testVAO);

	glBindBuffer(GL_ARRAY_BUFFER, testVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, testEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

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

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	//glBindVertexArray(0);

	//uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

//load and create a texture
void ATAT::loadTextures() {
	//unsigned int darkMetalTexture;
	//darkMetalTexture = SOIL_load_
	glGenTextures(1, &darkMetalTexture);
	glBindTexture(GL_TEXTURE_2D, darkMetalTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	//unsigned char* data = SOIL_load_image("resources/greymetal.jpg", &width, &height, &nrChannels, 0);
	unsigned char* data = stbi_load("resources/greymetal.jpg", &width, &height, &nrChannels, 0);

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
		std::cout << "Failed to load greymetalTexture" << std::endl;
	}

	stbi_image_free(data);
}

void ATAT::redrawBody()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, darkMetalTexture);

	glBindVertexArray(testVAO);
	glDrawElements(GL_TRIANGLES, 252, GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);
	//glActiveTexture(0);
}



void ATAT::drawLegSetup(GLfloat scale) {
	float vertices[] = {
		// positions                                                                    colors                  texture coord   normalvector

	//========== mittelteil ==========

	 //oberseite
	((legLength - slopedLegLengthMod) * scale), ((upperLegHeight + slopedLegHighthMod) * scale), ((legWidth)*scale),                1.0f, 1.0f, 1.0f,      1.0f, 1.0f,                              //0 vorne links
	((legLength - slopedLegLengthMod) * scale), ((upperLegHeight + slopedLegHighthMod) * scale), ((-legWidth) * scale),				1.0f, 1.0f, 1.0f,      1.0f, 0.0f,                            //0 vorne links    //1 vorne rechts
	((-legLength + slopedLegLengthMod) * scale), ((upperLegHeight + slopedLegHighthMod) * scale), ((-legWidth) * scale),			1.0f, 1.0f, 1.0f,      0.0f, 0.0f,                         //0 vorne links    //2 hinten rechts
	((-legLength + slopedLegLengthMod) * scale), ((upperLegHeight + slopedLegHighthMod) * scale), ((legWidth)*scale),				1.0f, 1.0f, 1.0f,      0.0f, 1.0f,                            //0 vorne links   //3 hinten links

	//schr<E4>gseite oben vorne
	((legLength - slopedLegLengthMod) * scale), ((upperLegHeight + slopedLegHighthMod) * scale), ((-legWidth) * scale),             1.0f, 1.0f, 1.0f,      0.2f, 0.2f,
	((legLength)*scale), ((upperLegHeight)*scale), ((-legWidth) * scale),                                                           1.0f, 1.0f, 1.0f,      0.2f, 0.0f,        //17
	((legLength)*scale), ((upperLegHeight)*scale), ((legWidth)*scale),                                                              1.0f, 1.0f, 1.0f,      0.0f, 0.0f,           //16
	((legLength - slopedLegLengthMod) * scale), ((upperLegHeight + slopedLegHighthMod) * scale), ((legWidth)*scale),				1.0f, 1.0f, 1.0f,      0.0f, 0.2f,

	//schr<E4>gseite oben hinten
	((-legLength + slopedLegLengthMod) * scale), ((upperLegHeight + slopedLegHighthMod) * scale), ((legWidth)*scale),               1.0f, 1.0f, 1.0f,      0.0f, 0.2f,
	((-legLength) * scale), ((upperLegHeight)*scale), ((legWidth)*scale),                                                           1.0f, 1.0f, 1.0f,      0.0f, 0.0f,           //16
	((-legLength) * scale), ((upperLegHeight)*scale), ((-legWidth) * scale),														1.0f, 1.0f, 1.0f,      0.2f, 0.0f,        //17
	((-legLength + slopedLegLengthMod) * scale), ((upperLegHeight + slopedLegHighthMod) * scale), ((-legWidth) * scale),            1.0f, 1.0f, 1.0f,      0.2f, 0.2f,

	//trapez rechts
	((legLength - slopedLegLengthMod) * scale), ((upperLegHeight + slopedLegHighthMod) * scale), ((legWidth)*scale),                1.0f, 1.0f, 1.0f,      1.0f, 1.0f,
	((legLength)*scale), ((upperLegHeight)*scale), ((legWidth)*scale),																1.0f, 1.0f, 1.0f,      1.0f, 0.0f,           //16
	((-legLength) * scale), ((upperLegHeight)*scale), ((legWidth)*scale),															1.0f, 1.0f, 1.0f,      0.0f, 0.0f,           //16
	((-legLength + slopedLegLengthMod) * scale), ((upperLegHeight + slopedLegHighthMod) * scale), ((legWidth)*scale),               1.0f, 1.0f, 1.0f,      0.0f, 1.0f,

	//trapez links
	((-legLength + slopedLegLengthMod) * scale), ((upperLegHeight + slopedLegHighthMod) * scale), ((-legWidth) * scale),            1.0f, 1.0f, 1.0f,      1.0f, 1.0f,
	((-legLength) * scale), ((upperLegHeight)*scale), ((-legWidth) * scale),														1.0f, 1.0f, 1.0f,      1.0f, 0.0f,           //16
	((legLength)*scale), ((upperLegHeight)*scale), ((-legWidth) * scale),															1.0f, 1.0f, 1.0f,      0.0f, 0.0f,           //16
	((legLength - slopedLegLengthMod) * scale), ((upperLegHeight + slopedLegHighthMod) * scale), ((-legWidth) * scale),				1.0f, 1.0f, 1.0f,      0.0f, 1.0f,

	//unterseite
	((legLength - slopedLegLengthMod) * scale), ((kneeHeight + slopedLegLowerHighthMod) * scale), ((legWidth)*scale),				1.0f, 1.0f, 1.0f,      1.0f, 1.0f,             //4
	((legLength - slopedLegLengthMod) * scale), ((kneeHeight + slopedLegLowerHighthMod) * scale), ((-legWidth) * scale),            1.0f, 1.0f, 1.0f,      1.0f, 0.0f,          //4//5
	((-legLength + slopedLegLengthMod) * scale), ((kneeHeight + slopedLegLowerHighthMod) * scale), ((-legWidth) * scale),           1.0f, 1.0f, 1.0f,      0.0f, 0.0f,      //4 //6
	((-legLength + slopedLegLengthMod) * scale), ((kneeHeight + slopedLegLowerHighthMod) * scale), ((legWidth)*scale),				1.0f, 1.0f, 1.0f,      0.0f, 1.0f,          //4//7

	//schr<E4>gseite unten vorne
	((legLength - slopedLegLengthMod) * scale), ((kneeHeight + slopedLegLowerHighthMod) * scale), ((-legWidth) * scale),            1.0f, 1.0f, 1.0f,      0.2f, 0.2f,
	((legLength)*scale), ((kneeHeight)*scale), ((-legWidth) * scale),																1.0f, 1.0f, 1.0f,      0.2f, 0.0f,        //17
	((legLength)*scale), ((kneeHeight)*scale), ((legWidth)*scale),                                                                  1.0f, 1.0f, 1.0f,      0.0f, 0.0f,           //16
	((legLength - slopedLegLengthMod) * scale), ((kneeHeight + slopedLegLowerHighthMod) * scale), ((legWidth)*scale),               1.0f, 1.0f, 1.0f,      0.0f, 0.2f,

	//schr<E4>gseite unten hinten
	((-legLength + slopedLegLengthMod) * scale), ((kneeHeight + slopedLegLowerHighthMod) * scale), ((legWidth)*scale),              1.0f, 1.0f, 1.0f,      0.0f, 0.2f,
	((-legLength) * scale), ((kneeHeight)*scale), ((legWidth)*scale),                                                               1.0f, 1.0f, 1.0f,      0.0f, 0.0f,           //16
	((-legLength) * scale), ((kneeHeight)*scale), ((-legWidth) * scale),                                                            1.0f, 1.0f, 1.0f,      0.2f, 0.0f,        //17
	((-legLength + slopedLegLengthMod) * scale), ((kneeHeight + slopedLegLowerHighthMod) * scale), ((-legWidth) * scale),           1.0f, 1.0f, 1.0f,      0.2f, 0.2f,

	//bei den seiten 0 und 1 oben, 2 und 3 unten
	//linke Seite
	((legLength)*scale), ((upperLegHeight)*scale), ((-legWidth) * scale),															1.0f, 1.0f, 1.0f,      1.0f, 1.0f,              //8
	((-legLength) * scale), ((upperLegHeight)*scale), ((-legWidth) * scale),														1.0f, 1.0f, 1.0f,      1.0f, 0.0f,           //9
	((-legLength) * scale), ((kneeHeight + slopedLegLowerHighthMod) * scale), ((-legWidth) * scale),								1.0f, 1.0f, 1.0f,      0.0f, 0.0f,               //10
	((legLength)*scale), ((kneeHeight + slopedLegLowerHighthMod) * scale), ((-legWidth) * scale),									1.0f, 1.0f, 1.0f,      0.0f, 1.0f,                  //11

	//rechte Seite
	((-legLength) * scale), ((upperLegHeight)*scale), ((legWidth)*scale),															1.0f, 1.0f, 1.0f,      1.0f, 1.0f,        //12
	((legLength)*scale), ((upperLegHeight)*scale), ((legWidth)*scale),																1.0f, 1.0f, 1.0f,      1.0f, 0.0f,           //13
	((legLength)*scale), ((kneeHeight + slopedLegLowerHighthMod) * scale), ((legWidth)*scale),										1.0f, 1.0f, 1.0f,      0.0f, 0.0f,               //14
	((-legLength) * scale), ((kneeHeight + slopedLegLowerHighthMod) * scale), ((legWidth)*scale),									1.0f, 1.0f, 1.0f,      0.0f, 1.0f,            //15

	//vordere Seite
	((legLength)*scale), ((upperLegHeight)*scale), ((legWidth)*scale),																1.0f, 1.0f, 1.0f,      1.0f, 1.0f,           //16
	((legLength)*scale), ((upperLegHeight)*scale), ((-legWidth) * scale),															1.0f, 1.0f, 1.0f,      1.0f, 0.0f,        //17
	((legLength)*scale), ((kneeHeight)*scale), ((-legWidth) * scale),																1.0f, 1.0f, 1.0f,      0.0f, 0.0f,            //18
	((legLength)*scale), ((kneeHeight)*scale), ((legWidth)*scale),																	1.0f, 1.0f, 1.0f,      0.0f, 1.0f,               //19

	//hintere Seite
	((-legLength) * scale), ((upperLegHeight)*scale), ((-legWidth) * scale),														1.0f, 1.0f, 1.0f,      1.0f, 1.0f,     //20
	((-legLength) * scale), ((upperLegHeight)*scale), ((legWidth)*scale),															1.0f, 1.0f, 1.0f,      1.0f, 0.0f,        //21
	((-legLength) * scale), ((kneeHeight)*scale), ((legWidth)*scale),																1.0f, 1.0f, 1.0f,      0.0f, 0.0f,            //22
	((-legLength) * scale), ((kneeHeight)*scale), ((-legWidth) * scale),															1.0f, 1.0f, 1.0f,      0.0f, 1.0f,         //23

	//has to be the last two ones
	//triangle left

	//triangle back right
	((-legLength)*scale), ((kneeHeight)*scale), ((legWidth)*scale),																	1.0f, 1.0f, 1.0f,      1.0f, 0.5f,               //19
	((-legLength) * scale), ((kneeHeight + slopedLegLowerHighthMod) * scale), ((legWidth)*scale),									1.0f, 1.0f, 1.0f,      1.0f, 0.0f,             //4
	((-legLength + slopedLegLengthMod) * scale), ((kneeHeight + slopedLegLowerHighthMod) * scale), ((legWidth)*scale),				1.0f, 1.0f, 1.0f,      0.0f, 0.0f,             //4

	//triangle back left
	((-legLength + slopedLegLengthMod) * scale), ((kneeHeight + slopedLegLowerHighthMod) * scale), ((-legWidth) * scale),			1.0f, 1.0f, 1.0f,      1.0f, 0.5f,             //4
	((-legLength)*scale), ((kneeHeight + slopedLegLowerHighthMod) * scale), ((-legWidth) * scale),									1.0f, 1.0f, 1.0f,      1.0f, 0.0f,             //4
	((-legLength)*scale), ((kneeHeight)*scale), ((-legWidth) * scale),																1.0f, 1.0f, 1.0f,      0.0f, 0.0f,               //19

	//triangle front right
	((legLength - slopedLegLengthMod) * scale), ((kneeHeight + slopedLegLowerHighthMod) * scale), ((legWidth)*scale),				1.0f, 1.0f, 1.0f,      1.0f, 0.5f,             //4
	((legLength) * scale), ((kneeHeight + slopedLegLowerHighthMod) * scale), ((legWidth)*scale),									1.0f, 1.0f, 1.0f,      1.0f, 0.0f,             //4
	((legLength)*scale), ((kneeHeight)*scale), ((legWidth)*scale),																	1.0f, 1.0f, 1.0f,      0.0f, 0.0f,               //19
	
	//triangle front left
	((legLength)*scale), ((kneeHeight)*scale), ((-legWidth)*scale),																	1.0f, 1.0f, 1.0f,      1.0f, 0.5f,               //19
	((legLength)*scale), ((kneeHeight + slopedLegLowerHighthMod) * scale), ((-legWidth) * scale),									1.0f, 1.0f, 1.0f,      1.0f, 0.0f,             //4
	((legLength - slopedLegLengthMod) * scale), ((kneeHeight + slopedLegLowerHighthMod) * scale), ((-legWidth) * scale),			1.0f, 1.0f, 1.0f,      0.0f, 0.0f,             //4


	};
	unsigned int indices[] = {  // note that we start from 0!
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
		30, 31, 28,

		32, 33, 34,
		34, 35, 32,

		36, 37, 38,
		38, 39, 36,

		40, 41, 42,
		42, 43, 40,

		44, 45, 46,
		46, 47, 44,

		48, 49, 50,

		51, 52, 53,

		54, 55, 56,

		57, 58, 59,
	};

	glGenVertexArrays(1, &legVAO);
	glGenBuffers(1, &legVBO);
	glGenBuffers(1, &legEBO);

	//bind the VAO first, then bind and set vertex buffer(s), then config vertex attributes.
	glBindVertexArray(legVAO);

	glBindBuffer(GL_ARRAY_BUFFER, legVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, legEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

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

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	//glBindVertexArray(0);

	//uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void ATAT::redrawLeg() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, darkMetalTexture);

	glBindVertexArray(legVAO);
	glDrawElements(GL_TRIANGLES, 84, GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);
	//glActiveTexture(0);
}


void ATAT::drawFootSetup(GLfloat scale) {

	
	float vertices[] = {

		//oberseite
		((legLength - slopedLegLengthMod) * scale), ((upperLegHeight + slopedLegHighthMod) * scale), ((legWidth)*scale),                1.0f, 1.0f, 1.0f,      1.0f, 1.0f,                              //0 vorne links
		((legLength - slopedLegLengthMod) * scale), ((upperLegHeight + slopedLegHighthMod) * scale), ((-legWidth) * scale),				1.0f, 1.0f, 1.0f,      1.0f, 0.0f,                            //0 vorne links    //1 vorne rechts
		((-legLength + slopedLegLengthMod) * scale), ((upperLegHeight + slopedLegHighthMod) * scale), ((-legWidth) * scale),			1.0f, 1.0f, 1.0f,      0.0f, 0.0f,                         //0 vorne links    //2 hinten rechts
		((-legLength + slopedLegLengthMod) * scale), ((upperLegHeight + slopedLegHighthMod) * scale), ((legWidth)*scale),				1.0f, 1.0f, 1.0f,      0.0f, 1.0f,                            //0 vorne links   //3 hinten links

		//schr<E4>gseite oben vorne
		((legLength - slopedLegLengthMod) * scale), ((upperLegHeight + slopedLegHighthMod) * scale), ((-legWidth) * scale),             1.0f, 1.0f, 1.0f,      0.0f, 0.1f,
		((legLength)*scale), ((upperLegHeight)*scale), ((-legWidth) * scale),                                                           1.0f, 1.0f, 1.0f,      0.0f, 0.0f,        //17
		((legLength)*scale), ((upperLegHeight)*scale), ((legWidth)*scale),                                                              1.0f, 1.0f, 1.0f,      1.0f, 0.0f,           //16
		((legLength - slopedLegLengthMod) * scale), ((upperLegHeight + slopedLegHighthMod) * scale), ((legWidth)*scale),				1.0f, 1.0f, 1.0f,      1.0f, 1.0f,

		//schr<E4>gseite oben hinten
		((-legLength + slopedLegLengthMod) * scale), ((upperLegHeight + slopedLegHighthMod) * scale), ((legWidth)*scale),               1.0f, 1.0f, 1.0f,      0.0f, 0.2f,
		((-legLength) * scale), ((upperLegHeight)*scale), ((legWidth)*scale),                                                           1.0f, 1.0f, 1.0f,      0.0f, 0.0f,           //16
		((-legLength) * scale), ((upperLegHeight)*scale), ((-legWidth) * scale),														1.0f, 1.0f, 1.0f,      0.2f, 0.0f,        //17
		((-legLength + slopedLegLengthMod) * scale), ((upperLegHeight + slopedLegHighthMod) * scale), ((-legWidth) * scale),            1.0f, 1.0f, 1.0f,      0.2f, 0.2f,

		//trapez rechts
		((legLength - slopedLegLengthMod) * scale), ((upperLegHeight + slopedLegHighthMod) * scale), ((legWidth)*scale),                1.0f, 1.0f, 1.0f,      1.0f, 1.0f,
		((legLength)*scale), ((upperLegHeight)*scale), ((legWidth)*scale),																1.0f, 1.0f, 1.0f,      1.0f, 0.0f,           //16
		((-legLength) * scale), ((upperLegHeight)*scale), ((legWidth)*scale),															1.0f, 1.0f, 1.0f,      0.0f, 0.0f,           //16
		((-legLength + slopedLegLengthMod) * scale), ((upperLegHeight + slopedLegHighthMod) * scale), ((legWidth)*scale),               1.0f, 1.0f, 1.0f,      0.0f, 1.0f,

		//trapez links
		((-legLength + slopedLegLengthMod) * scale), ((upperLegHeight + slopedLegHighthMod) * scale), ((-legWidth) * scale),            1.0f, 1.0f, 1.0f,      0.0f, 1.0f,
		((-legLength) * scale), ((upperLegHeight)*scale), ((-legWidth) * scale),														1.0f, 1.0f, 1.0f,      0.0f, 0.0f,           //16
		((legLength)*scale), ((upperLegHeight)*scale), ((-legWidth) * scale),															1.0f, 1.0f, 1.0f,      1.0f, 0.0f,           //16
		((legLength - slopedLegLengthMod) * scale), ((upperLegHeight + slopedLegHighthMod) * scale), ((-legWidth) * scale),				1.0f, 1.0f, 1.0f,      1.0f, 1.0f,

		//fuß, 2 Trapeze?

		//vorderes oben
		
		((0) * scale), ((upperLegHeight)*scale), ((-legLength - footLengthMod) * scale),                1.0f, 1.0f, 1.0f,      0.0f, 1.0f,
		((0) * scale), ((upperLegHeight)*scale), ((legLength + footLengthMod) * scale),				1.0f, 1.0f, 1.0f,      0.0f, 0.0f,
		((legLength + footLengthMod) * scale), ((upperLegHeight)*scale), ((legLength)*scale),			1.0f, 1.0f, 1.0f,      1.0f, 0.0f,
		((legLength + footLengthMod) * scale), ((upperLegHeight)*scale), ((-legLength) * scale),		1.0f, 1.0f, 1.0f,      1.0f, 1.0f,

		//hinteres oben
		((-legLength - footLengthMod) * scale), ((upperLegHeight)*scale), ((-legLength) * scale),		1.0f, 1.0f, 1.0f,      1.0f, 1.0f,
		((-legLength - footLengthMod) * scale), ((upperLegHeight)*scale), ((legLength)*scale),			1.0f, 1.0f, 1.0f,      1.0f, 0.0f,
		((0) * scale), ((upperLegHeight)*scale), ((legLength + footLengthMod) * scale),					1.0f, 1.0f, 1.0f,      0.0f, 0.0f,
		((0) * scale), ((upperLegHeight)*scale), ((-legLength - footLengthMod) * scale),                1.0f, 1.0f, 1.0f,      0.0f, 1.0f,



		//vorderes unten
		((legLength + footLengthMod) * scale), ((upperLegHeight - foothight)*scale), ((-legLength) * scale),		1.0f, 1.0f, 1.0f,      1.0f, 1.0f,
		((legLength + footLengthMod) * scale), ((upperLegHeight - foothight)*scale), ((legLength)*scale),			1.0f, 1.0f, 1.0f,      1.0f, 0.0f,
		((0) * scale), ((upperLegHeight - foothight)*scale), ((legLength + footLengthMod) * scale),					1.0f, 1.0f, 1.0f,      0.0f, 0.0f,
		((0) * scale), ((upperLegHeight - foothight)*scale), ((-legLength - footLengthMod) * scale),                1.0f, 1.0f, 1.0f,      0.0f, 1.0f,
		
		//hinteres unten
		((0) * scale), ((upperLegHeight - foothight)*scale), ((-legLength - footLengthMod) * scale),                1.0f, 1.0f, 1.0f,      0.0f, 1.0f,
		((0) * scale), ((upperLegHeight - foothight)*scale), ((legLength + footLengthMod) * scale),					1.0f, 1.0f, 1.0f,      0.0f, 0.0f,
		((-legLength - footLengthMod ) * scale), ((upperLegHeight - foothight)*scale), ((legLength)*scale),			1.0f, 1.0f, 1.0f,      1.0f, 0.0f,
		((-legLength - footLengthMod) * scale), ((upperLegHeight - foothight)*scale), ((-legLength) * scale),		1.0f, 1.0f, 1.0f,      1.0f, 1.0f,
		
		//vorderseite
		((legLength + footLengthMod) * scale), ((upperLegHeight)*scale), ((-legLength) * scale),					1.0f, 1.0f, 1.0f,      1.0f, 1.0f,
		((legLength + footLengthMod) * scale), ((upperLegHeight - foothight) * scale), ((-legLength) * scale),		1.0f, 1.0f, 1.0f,      1.0f, 0.0f,
		((legLength + footLengthMod) * scale), ((upperLegHeight - foothight) * scale), ((legLength)*scale),			1.0f, 1.0f, 1.0f,      0.0f, 0.0f,
		((legLength + footLengthMod) * scale), ((upperLegHeight)*scale), ((legLength)*scale),						1.0f, 1.0f, 1.0f,      0.0f, 1.0f,
		
		//hinterseite
		
		((-legLength - footLengthMod) * scale), ((upperLegHeight)*scale), ((legLength)*scale),						1.0f, 1.0f, 1.0f,      0.0f, 1.0f,
		((-legLength - footLengthMod) * scale), ((upperLegHeight - foothight) * scale), ((legLength)*scale),		1.0f, 1.0f, 1.0f,      0.0f, 0.0f,
		((-legLength - footLengthMod) * scale), ((upperLegHeight - foothight) * scale), ((-legLength) * scale),		1.0f, 1.0f, 1.0f,      1.0f, 0.0f,
		((-legLength - footLengthMod) * scale), ((upperLegHeight)*scale), ((-legLength) * scale),					1.0f, 1.0f, 1.0f,      1.0f, 1.0f,

		//schräg rechts vorne
		((legLength + footLengthMod) * scale), ((upperLegHeight)*scale), ((legLength) * scale),					1.0f, 1.0f, 1.0f,      1.0f, 1.0f,
		((legLength + footLengthMod) * scale), ((upperLegHeight - foothight)*scale), ((legLength)*scale),		1.0f, 1.0f, 1.0f,      1.0f, 0.0f,
		((0) * scale), ((upperLegHeight - foothight)*scale), ((legLength + footLengthMod) * scale),				1.0f, 1.0f, 1.0f,      0.0f, 0.0f,
		((0) * scale), ((upperLegHeight)*scale), ((legLength + footLengthMod) * scale),							1.0f, 1.0f, 1.0f,      0.0f, 1.0f,

		//schräg rechts hinten		
		((0) * scale), ((upperLegHeight)*scale), ((legLength + footLengthMod) * scale),							1.0f, 1.0f, 1.0f,      0.0f, 1.0f,
		((0) * scale), ((upperLegHeight - foothight) * scale), ((legLength + footLengthMod) * scale),			1.0f, 1.0f, 1.0f,      0.0f, 0.0f,
		((-legLength - footLengthMod) * scale), ((upperLegHeight - foothight) * scale), ((legLength)*scale),	1.0f, 1.0f, 1.0f,      1.0f, 0.0f,
		((-legLength - footLengthMod) * scale), ((upperLegHeight)*scale), ((legLength)*scale),					1.0f, 1.0f, 1.0f,      1.0f, 1.0f,


		//schräg links vorne
		((legLength + footLengthMod) * scale), ((upperLegHeight)*scale), ((-legLength)*scale),					1.0f, 1.0f, 1.0f,      1.0f, 1.0f,
		((0) * scale), ((upperLegHeight)*scale), ((-legLength - footLengthMod) * scale),							1.0f, 1.0f, 1.0f,      0.0f, 1.0f,
		((0) * scale), ((upperLegHeight - foothight) * scale), ((-legLength - footLengthMod) * scale),				1.0f, 1.0f, 1.0f,      0.0f, 0.0f,
		((legLength + footLengthMod) * scale), ((upperLegHeight - foothight) * scale), ((-legLength) * scale),		1.0f, 1.0f, 1.0f,      1.0f, 0.0f,

		//schräg links hinten
		((-legLength - footLengthMod) * scale), ((upperLegHeight)*scale), ((-legLength)*scale),					1.0f, 1.0f, 1.0f,      1.0f, 1.0f,
		((-legLength - footLengthMod)* scale), ((upperLegHeight - foothight)* scale), ((-legLength)* scale),	1.0f, 1.0f, 1.0f,      1.0f, 0.0f,
		((0)* scale), ((upperLegHeight - foothight)* scale), ((-legLength - footLengthMod)* scale),			1.0f, 1.0f, 1.0f,      0.0f, 0.0f,
		((0)* scale), ((upperLegHeight)*scale), ((-legLength - footLengthMod)* scale),							1.0f, 1.0f, 1.0f,      0.0f, 1.0f,



	};

	unsigned int indices[] = {  // note that we start from 0!

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
		30, 31, 28,

		32, 33, 34,
		34, 35, 32,

		36, 37, 38,
		38, 39, 36,

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

	};

	glGenVertexArrays(1, &footVAO);
	glGenBuffers(1, &footVBO);
	glGenBuffers(1, &footEBO);

	//bind the VAO first, then bind and set vertex buffer(s), then config vertex attributes.
	glBindVertexArray(footVAO);

	glBindBuffer(GL_ARRAY_BUFFER, footVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, footEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

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


void ATAT::redrawFoot() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, darkMetalTexture);

	glBindVertexArray(footVAO);
	glDrawElements(GL_TRIANGLES, 90, GL_UNSIGNED_INT, 0);
}



void ATAT::initialDraw(glm::mat4 mView, glm::vec3 lightPos, glm::vec3 camPos) {
	glm::mat4 model = glm::mat4(1.0f);
	atatShader.use();
	atatShader.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
	atatShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	atatShader.setVec3("lightDirection", lightPos);
	atatShader.setVec3("viewPos", camPos);

	// View/Projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)2100 / (float)1200, 0.1f, 100.0f);
	glm::mat4 view = mView;
	atatShader.setMat4("projection", projection);
	atatShader.setMat4("view", view);

	model = glm::mat4(1.0f);
	//model = glm::rotate(model, glm::radians((float)60), glm::vec3(0.0, 1.0, 0.0));
	atatShader.setMat4("model", model);

	drawBodySetup(scale); // drawBodySetup
	drawLegSetup(scale);
	drawFootSetup(scale);
	/* glm::mat4 trans = glm::mat4(1.0f);
	 trans = glm::translate(trans, glm::vec3(bLength * 2, 0.0f, bLowerWidth * 2));
	 atatShader.setMat4("model", trans);*/

	 /* model = glm::rotate(model, glm::radians((float)60), glm::vec3(0.0, 1.0, 0.0));
	  atatShader.setMat4("model", model);*/

	  //atat.redrawUpperLeg();
	  //model = glm::rotate(model, glm::radians((float)60), glm::vec3(0.0, 1.0, 0.0));
	  //sm.setMat4("model", model);
	  //atat.redrawBody();
}

void ATAT::redrawATAT() {
	//local vars
	//GLfloat velocity = forwardMovement / 100;
	GLfloat walkingRad = forwardMovementRLU;
	GLfloat velocity = speed;

	animateBody(velocity, walkingRad);
}

void ATAT::animateBody(GLfloat velocity, GLfloat upperLegAngle) {
	glm::mat4 model = glm::mat4(1.0f);

	GLfloat rotation = sidewardRotation;
	GLfloat forwardSpeed = 0;

	//taste gedr?ckt oder nicht, wird am Ende wieder resettet. Wird ein Schritt gemacht oder nicht
	if (speed > 0) {
		speed = 1;
	}
	else {
		speed = 0;
	}

	//im Endeffekt 1 oder 0, je nachdem ob es weitergehen soll oder nicht. Kann sp?ter noch ver?ndert werden.
	forwardSpeed = speed / 500;

	GLfloat newX = 0;
	GLfloat newZ = 0;

	//seiten f?r den neuen Vector berechnen. forwardSpeed ist entweder 0 oder 1
	if (forwardSpeed != 0) {
		calcSides(newX, newZ, forwardSpeed, rotation);
	}
	else {
		newX = 0;
		newZ = 0;
	}

	model = glm::translate(model, glm::vec3(0, -0.1f, 0));
	atatShader.setMat4("model", model);

	//zur?ck zum Ursprung
	model = glm::translate(model, glm::vec3(currentX + newX, 0.0, currentZ + newZ));
	atatShader.setMat4("model", model);

	//im Ursprung Rotieren
	model = glm::rotate(model, glm::radians((float)(rotation)), glm::vec3(0.0, 1.0, 0.0));
	atatShader.setMat4("model", model);

	//zeichnen
	redrawBody();
	//vorne rechts
	animateLeg(model, (currentX + newX), (currentZ + newZ), forwardMovementRLU, lowerLegMovRF, rotation, 0);
	//hinten rechts
	animateLeg(model, (currentX + newX), (currentZ + newZ), forwardMovementRLB, lowerLegMovRB, rotation, 1);
	//vorne links
	animateLeg(model, (currentX + newX), (currentZ + newZ), forwardMovementLUF, lowerLegMovLF, rotation, 2);
	//hinten links
	animateLeg(model, (currentX + newX), (currentZ + newZ), forwardMovementLUB, lowerLegMovLB, rotation, 3);

	

	currentAngle = rotation;
	currentX = currentX + newX;
	currentZ = currentZ + newZ;
	speed = 0;
}

void ATAT::animateLeg(glm::mat4 model, GLfloat x, GLfloat z, GLfloat upperLegAngle, GLfloat lowerAngle, GLfloat rotation, short type) {
	//vars

	GLfloat legPosX = 0;
	GLfloat legPosZ = 0;

	//vorne rechts
	if (type == 0) {
		legPosX = bLength;
		legPosZ = bLowerWidth;
	}
	//hinten rechts
	else if (type == 1) {
		legPosX = -bLength;
		legPosZ = bLowerWidth;
	}
	//vorne links
	else if (type == 2) {
		legPosX = bLength;
		legPosZ = -bLowerWidth;
	}
	//hinten links
	else if (type == 3) {
		legPosX = -bLength;
		legPosZ = -bLowerWidth;
	}

	//h?he des Beins
	GLfloat height = upperLegHeight * scale;

	//========== movement des oberen Beins ==========

	//zum richtigen Platz am ATAT
	model = glm::translate(model, glm::vec3(((legPosX * 2)), (height), (legPosZ)));
	atatShader.setMat4("model", model);

	model = glm::rotate(model, glm::radians((float)upperLegAngle), glm::vec3(0.0, 0.0, 1.0));
	atatShader.setMat4("model", model);

	model = glm::translate(model, glm::vec3(0.0, -height, 0.0));
	atatShader.setMat4("model", model);

	//oberschenkel
	redrawLeg();

	//hier die animation des unterschenkels

	model = glm::translate(model, glm::vec3(((0)), (height / 2) + 0.125f, (0)));
	atatShader.setMat4("model", model);

	model = glm::rotate(model, glm::radians((float)lowerAngle), glm::vec3(0.0, 0.0, 1.0));
	atatShader.setMat4("model", model);

	model = glm::translate(model, glm::vec3(0.0, -height, 0.0));
	atatShader.setMat4("model", model);

	redrawLeg();

	model = glm::translate(model, glm::vec3(((0)), (height / 2) + 0.125f, (0)));
	atatShader.setMat4("model", model);

	model = glm::rotate(model, glm::radians((float)-(lowerAngle+ upperLegAngle)), glm::vec3(0.0, 0.0, 1.0));
	atatShader.setMat4("model", model);

	model = glm::translate(model, glm::vec3(0.0, -height, 0.0));
	atatShader.setMat4("model", model);

	redrawFoot();

	

	//vorne rechts
	//animateFoot(model, (legPosX), height, (legPosZ), forwardMovementLUB, lowerLegMovLB, (upperLegAngle + rotation), 0);

}


void ATAT::animateFoot(glm::mat4 model, GLfloat x, GLfloat y, GLfloat z, GLfloat upperLegAngle, GLfloat lowerAngle, GLfloat rotation, short type) {

	GLfloat legPosX = x;
	GLfloat legPosZ = z;
	GLfloat height = y;


	/*
	model = glm::translate(model, glm::vec3(((legPosX * 2)), (-0.625f), (legPosZ)));
	atatShader.setMat4("model", model);

	

	model = glm::translate(model, glm::vec3((-(legPosX * 2)), (0), (-legPosZ)));
	atatShader.setMat4("model", model);
	*/
	/*
	
	*/

	//model = glm::translate(model, glm::vec3((((0))), (-0.625f), (0)));
	//atatShader.setMat4("model", model);

	//model = glm::translate(model, glm::vec3(0.0, -height, 0.0));
	//atatShader.setMat4("model", model);



	//model = glm::rotate(model, glm::radians((float)45), glm::vec3(0.0, 0.0, 1.0));
	//atatShader.setMat4("model", model);

	redrawFoot();
}

void ATAT::changeAnimateValues() {
	//funktioniert noch nicht 100%, da weiter gemacht wird.

	//// Calculate delta time
	//float currentFrame = glfwGetTime();
	//g_dt = currentFrame - g_lf;
	//g_lf = currentFrame;

	speed++;

	//deltatime bleibt einigermaßen konstant bei 0.007
	double currentTime = glfwGetTime();
	double deltaTime = currentTime - lastFrameTime;
	lastFrameTime = currentTime;
	frames++;

	GLfloat div = 0.25;

	//========== rechts vorne ==========
	//von ganz vorne nach hinten
	if (forwardMovementRLU > -24 && legStateRF == false) {
		forwardMovementRLU -= (0.25 * div);
	}
	//Bein ganz hinten angekommen, soll jetzt wieder nach vorne gehen
	else if (forwardMovementRLU == -24 && legStateRF == false) {
		legStateRF = true;
	}
	//Bein l?uft nach vorne
	else if (forwardMovementRLU < 24 && legStateRF == true) {
		forwardMovementRLU += (1 * div);

		//unterschenkel
		if (forwardMovementRLU <= 0) {
			lowerLegMovRF -= (2 * div);
		}
		else if (forwardMovementRLU >= 0 && forwardMovementRLU <= 24) {
			lowerLegMovRF += (2 * div);
		}
	}
	else if (forwardMovementRLU >= 24 && legStateRF == true) {
		legStateRF = false;
	}

	//========== links vorne ==========
	//von ganz vorne nach hinten
	if (forwardMovementLUF > -24 && legStateLF == false) {
		forwardMovementLUF -= (0.25 * div);
	}
	//Bein ganz hinten angekommen, soll jetzt wieder nach vorne gehen
	else if (forwardMovementLUF == -24 && legStateLF == false) {
		legStateLF = true;
	}
	//Bein l?uft nach vorne
	else if (forwardMovementLUF < 24 && legStateLF == true) {
		forwardMovementLUF += (1 * div);

		//unterschenkel
		if (forwardMovementLUF <= 0) {
			lowerLegMovLF -= (2 * div);
		}
		else if (forwardMovementLUF >= 0 && forwardMovementLUF <= 24) {
			lowerLegMovLF += (2 * div);
		}
	}
	else if (forwardMovementLUF >= 24 && legStateLF == true) {
		legStateLF = false;
	}

	//========== rechts hinten ==========
	//von ganz vorne nach hinten
	if (forwardMovementRLB > -24 && legStateRB == false) {
		forwardMovementRLB -= (0.25 * div);
	}
	//Bein ganz hinten angekommen, soll jetzt wieder nach vorne gehen
	else if (forwardMovementRLB == -24 && legStateRB == false) {
		legStateRB = true;
	}
	//Bein l?uft nach vorne
	else if (forwardMovementRLB < 24 && legStateRB == true) {
		forwardMovementRLB += (1 * div);

		//unterschenkel
		if (forwardMovementRLB <= 0) {
			lowerLegMovRB -= (2 * div);
		}
		else if (forwardMovementRLB >= 0 && forwardMovementRLB <= 24) {
			lowerLegMovRB += (2 * div);
		}
	}
	else if (forwardMovementRLB >= 24 && legStateRB == true) {
		legStateRB = false;
	}

	//========== links hinten ==========
	//von ganz vorne nach hinten
	if (forwardMovementLUB > -24 && legStateLB == false) {
		forwardMovementLUB -= (0.25 * div);
	}
	//Bein ganz hinten angekommen, soll jetzt wieder nach vorne gehen
	else if (forwardMovementLUB == -24 && legStateLB == false) {
		legStateLB = true;
	}
	//Bein l?uft nach vorne
	else if (forwardMovementLUB < 24 && legStateLB == true) {
		forwardMovementLUB += (1 * div);

		//unterschenkel
		if (forwardMovementLUB <= 0) {
			lowerLegMovLB -= (2 * div);
		}
		else if (forwardMovementLUB >= 0 && forwardMovementLUB <= 24) {
			lowerLegMovLB += (2 * div);
		}
	}
	else if (forwardMovementLUB >= 24 && legStateLB == true) {
		legStateLB = false;
	}
}

void ATAT::changeRotation() {
	if (sidewardRotation >= 360 || sidewardRotation <= -360) {
		sidewardRotation = 0;
	}
}