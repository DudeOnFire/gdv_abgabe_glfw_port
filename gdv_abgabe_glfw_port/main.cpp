//------------ GDV-Projekt ----------------
// Authors: Dennis Wilpert, Henrik Trübenbach
// OpenGL version: 3.3
// 
//------------ Includes --------------------
#include <glad/glad.h> // Glad first, then GLFW
#include <GLFW/glfw3.h>
#include <iostream>
#include "ATAT.h"
#include "Lighting.h"
#include "Skybox.h"
#include "Camera.h"

//------------ Global Variables -------------
// Notation: 
// --> g_ for global vars
// --> All const vars in uppercase letters
// --> G_ for global objects
// 
int g_windowSizeX = 2200;
int g_windowSizeY = 1200;
float g_dt = 0.0f;
float g_lf = 0.0f;
float g_lastX = (float)g_windowSizeX / 2.0;
float g_lastY = (float)g_windowSizeY / 2.0;
bool g_firstMouseInput = true;
unsigned int g_cubemapID;
glm::vec3 g_lightPos(1.2f, 1.0f, 2.0f);
Lighting G_light;
ATAT G_atat;
Skybox G_skybox;
Camera G_camera = Camera(glm::vec3(0.5f, 2.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f));


//------------- Declarations ---------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window);
//void drawGrid();

//------------- Main function ---------------
int main() {

	// Initialize GL context and set version info
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window object
	GLFWwindow* window = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "GDV-Projekt", NULL, NULL);
	if (window == NULL) {

		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	// Capture mouse pointer
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Load GLAD to handle function pointers for OpenGL, needs to happen before any call to an OpenGL function.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	// Initialization of all objects happens here
	//Initialization();
	// Initialize GL aspects
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	//glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glFrontFace(GL_CCW);
	// glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations --Doesn't exist in glfw...


	// Light shader
	G_light.lightCubeShader = Shader("shaders/light_cube.vs", "shaders/light_cube.fs");
	G_light.lightingShader = Shader("shaders/lighting.vs", "shaders/lighting.fs");

	// Skybox shader
	G_skybox.skyboxShader = Shader("shaders/skybox_vs.vs", "shaders/skybox_fs.fs");

	// ATAT shader
	G_atat.atatShader = Shader("shaders/atat_vs.vs", "shaders/atat_fs.fs");

	// Call init functions of objects
	G_atat.atatShader.use();
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)g_windowSizeX / (float)g_windowSizeY, 0.1f, 100.0f);
	G_atat.atatShader.setMat4("projection", projection);
	G_atat.loadTextures();

	G_atat.atatShader.setInt("darkMetalTexture", 0);
	G_atat.drawBodySetup(2);
	G_atat.drawLFUpperLegSetup(2);

	G_light.prepareLight();
	g_cubemapID = G_skybox.loadSkybox();


	// Our new RenderScene function, the main loop
	while (!glfwWindowShouldClose(window)) {

		// Calculate delta time
		float currentFrame = glfwGetTime();
		g_dt = currentFrame - g_lf;
		g_lf = currentFrame;

		// Process Input
		processInput(window);

		// Set background color to black
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 0.5f);							// Black Background					
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// Draw our objects
		G_light.generateLight(G_camera.getViewMatrix(), g_lightPos, G_camera.mView);

		G_atat.atatShader.use();

		glm::mat4 model = glm::mat4(1.0f);
		G_atat.atatShader.setMat4("model", model);
		// drawGrid();

		glm::mat4 view = G_camera.getViewMatrix();
		G_atat.atatShader.setMat4("view", view);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)g_windowSizeX / (float)g_windowSizeY, 0.1f, 100.0f);
		G_atat.atatShader.setMat4("projection", projection);

		G_atat.initialDraw();

		G_skybox.drawSkybox(G_camera.getViewMatrix(), g_cubemapID);



		// Swap buffers and get new events
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwTerminate();
	return 0;
}


// Resize callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {

	glViewport(0, 0, width, height);
}

// Mouse callback function
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

	// Check if first mouse input to avoid sudden and large movement jump
	if (g_firstMouseInput) {

		g_lastX = xpos;
		g_lastY = ypos;
		g_firstMouseInput = false;
	}

	// Calculate offset
	float xoffset = xpos - g_lastX;
	float yoffset = g_lastY - ypos;
	g_lastX = xpos;
	g_lastY = ypos;

	// Multiply with sensitivity to make movement more smooth
	xoffset *= SENSITIVITY;
	yoffset *= SENSITIVITY;

	// Add calculated offset to camera pitch and yaw
	G_camera.yaw += xoffset;
	G_camera.pitch += yoffset;

	// Set constraints so the camera can't move more than 180 degrees total in the vertical direction
	if (G_camera.pitch > 89.0f)
		G_camera.pitch = 89.0f;
	if (G_camera.pitch < -89.0f)
		G_camera.pitch = -89.0f;

	//G_camera.handleMouseInput(xoffset, yoffset, true);


	// Calculate the actual direction vector for the mouse
	glm::vec3 direction;
	direction.x = cos(glm::radians(G_camera.yaw)) * cos(glm::radians(G_camera.pitch));
	direction.y = sin(glm::radians(G_camera.pitch));
	direction.z = sin(glm::radians(G_camera.yaw)) * cos(glm::radians(G_camera.pitch));
	G_camera.mView = glm::normalize(direction);
	
}

// Query GLFW for key presses
void processInput(GLFWwindow* window) {

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {

		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		G_camera.handleKeyboardInput(UP, g_dt);
		std::cout << "W key pressed" << std::endl;
		G_camera.outputmPosition();
		G_camera.outputmView();
	}
		
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		G_camera.handleKeyboardInput(DOWN, g_dt);
		std::cout << "S key pressed" << std::endl;
		G_camera.outputmPosition();
		G_camera.outputmView();
	}
		
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		G_camera.handleKeyboardInput(LEFT, g_dt);
		std::cout << "A key pressed" << std::endl;
		G_camera.outputmPosition();
		G_camera.outputmView();
	}
		
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		G_camera.handleKeyboardInput(RIGHT, g_dt);
		std::cout << "D key pressed" << std::endl;
		G_camera.outputmPosition();
		G_camera.outputmView();
	}
}


//// Draw grid
//void drawGrid() {
//
//	for (float i = -500; i <= 500; i += 5)
//	{
//		glBegin(GL_LINES);
//		glColor3ub(0, 0, 0);
//		glVertex3f(-500, 0, i);
//		glVertex3f(500, 0, i);
//		glVertex3f(i, 0, -500);
//		glVertex3f(i, 0, 500);
//		glEnd();
//	}
//}