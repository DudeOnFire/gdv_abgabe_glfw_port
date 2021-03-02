#include "Landscape.h"

void Landscape::loadLandscape()
{
	

	// Generate vertices for 2D plane
	float vertices[] = {

		// positions	   // colors		  // texture coords  // normal vectors
		-1.0f, 0.0f, -1.0f,  1.0f, 1.0f, 1.0f,  80.0f, 80.0f,   0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, -1.0f,  1.0f, 1.0f, 1.0f,  80.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		-1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 80.0f,		0.0f, 1.0f, 0.0f,
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

	//--------- Textures ----------------------------

	// Create the snow textures
	snowTexture = loadTexture("resources/snow_texture.jpg");
	
}

void Landscape::drawLandscape(glm::mat4 mView, glm::vec3 lightPos, glm::vec3 camPos)
{
	
	// Use shaders for lighting
	landscapeShader.use();
	landscapeShader.setVec3("objectColor", 1.0f, 1.0f, 1.0f); 
	landscapeShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f); 
	landscapeShader.setVec3("lightDirection", lightPos);
	landscapeShader.setVec3("viewPos", camPos);
	

	// View / Projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)2100 / (float)1200, 0.1f, 100.0f);
	glm::mat4 view = mView;
	landscapeShader.setMat4("projection", projection);
	landscapeShader.setMat4("view", view);
	
	// Set model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(2000.0f));
	landscapeShader.setMat4("model", model);
	
	// Bind texture and draw
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, snowTexture);
	glBindVertexArray(scapeVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

unsigned int Landscape::loadTexture(const char* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
