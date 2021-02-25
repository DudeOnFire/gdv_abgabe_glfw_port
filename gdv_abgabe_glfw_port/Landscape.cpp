#include "Landscape.h"

void Landscape::loadLandscape()
{
	

	// Generate vertices for 2D plane
	float vertices[] = {

		// positions	   // colors		  // texture coords
		1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	};

	unsigned int indices[] = {
		0, 1, 3,	// First triangle
		1, 2, 3		// Second triangle
	};

	// Fill VBO, EBO and VAO
	glGenVertexArrays(1, &scapeVAO);
	glGenBuffers(1, &scapeVBO);
	glGenBuffers(1, &scapeEBO);
	glBindVertexArray(scapeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, scapeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, scapeEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Notify OpenGL of new vertex attributes
	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//--------- Texture ----------------------------

	// Create the snow texture
	glGenTextures(1, &snowTexture);
	glBindTexture(GL_TEXTURE_2D, snowTexture);

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("resources/snow_texture.jpg", &width, &height, &nrChannels, 0);

	if (data) {

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {

		std::cout << "Failed to load snow texture" << std::endl;
	}
	stbi_image_free(data);

}

void Landscape::drawLandscape()
{

	// Bind texture
	glActiveTexture(1);
	glBindTexture(GL_TEXTURE_2D, snowTexture);
	glBindVertexArray(scapeVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}
