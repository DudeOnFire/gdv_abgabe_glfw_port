#include "Landscape.h"

void Landscape::loadLandscape()
{
	

	// Generate vertices for 2D plane
	float vertices[] = {

		// positions	   // colors		  // texture coords  // normal vectors
		-1.0f, 0.0f, -1.0f,  1.0f, 1.0f, 1.0f,  100.0f, 100.0f,   0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, -1.0f,  1.0f, 1.0f, 1.0f,  100.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		-1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 100.0f,		0.0f, 1.0f, 0.0f,
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	// Normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(3);

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
	unsigned char* data = stbi_load("resources/greymetal.jpg", &width, &height, &nrChannels, 0);

	if (data) {

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {

		std::cout << "Failed to load snow texture" << std::endl;
	}
	stbi_image_free(data);

}

void Landscape::drawLandscape(glm::mat4 mView, glm::vec3 lightPos, glm::vec3 camPos)
{
	
	// Use shaders for lighting
	landscapeShader.use();
	landscapeShader.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
	landscapeShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	landscapeShader.setVec3("lightPos", lightPos);
	landscapeShader.setVec3("viewPos", camPos);

	// View / Projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)2100 / (float)1200, 0.1f, 100.0f);
	glm::mat4 view = mView;
	landscapeShader.setMat4("projection", projection);
	landscapeShader.setMat4("view", view);
	
	// Set model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(10.0f));
	landscapeShader.setMat4("model", model);
	
	// Bind texture
	glActiveTexture(1);
	glBindTexture(GL_TEXTURE_2D, snowTexture);
	glBindVertexArray(scapeVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}
