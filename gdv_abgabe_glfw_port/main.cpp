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
#include "Landscape.h"

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
bool g_toggleNormalVectors = false;
glm::vec3 g_lightPos(2.0f, 10.0f, 5.0f);
glm::vec3 g_flDirection(0.5f, 1.0f, 0.0f);
glm::vec3 g_flPosition(0.5f, 1.0f, 0.0f);
float g_cutOffAngle = 12.5f;
float g_outerCutOffAngle = 17.5f;
Lighting G_light;
ATAT G_atat;
Skybox G_skybox;
Camera G_camera = Camera(glm::vec3(2.0f, 4.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
Landscape G_scape;


//------------- Declarations ---------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window);


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
	Shader atatShader = Shader("shaders/atat_vs.vs", "shaders/atat_fs.fs", "shaders/atat_gs.gs"); //"shaders/atat_gs.gs"
	Shader normalDrawShader = Shader("shaders/normal_display_vs.vs", "shaders/normal_display_fs.fs", "shaders/normal_display_gs.gs");
	G_atat.atatShader = atatShader;

	// Landscape shader
	Shader landscapeShader = Shader("shaders/landscape_vs.vs", "shaders/landscape_fs.fs");
	G_scape.landscapeShader = landscapeShader;

	// Call init functions of objects
	G_atat.atatShader.use();
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)g_windowSizeX / (float)g_windowSizeY, 0.1f, 100.0f);
	G_atat.atatShader.setMat4("projection", projection);
	G_atat.loadTextures();
	G_atat.atatShader.setInt("darkMetalTexture", 0);
	G_atat.initialDraw(G_camera.getViewMatrix(), g_lightPos, G_camera.mView);

	G_light.prepareLight();
	g_cubemapID = G_skybox.loadSkybox();

	// Landscape
	G_scape.landscapeShader.use();
	G_scape.landscapeShader.setInt("snowTexture", 1);
	G_scape.landscapeShader.setMat4("projection", projection);
	G_scape.loadLandscape();


	// Our new RenderScene function, the main loop
	while (!glfwWindowShouldClose(window)) {

		// Calculate delta time
		float currentFrame = glfwGetTime();
		g_dt = currentFrame - g_lf;
		g_lf = currentFrame;

		// Process Input
		processInput(window);

		// Change light position
		//g_lightPos.x = 3.0f * sin(glfwGetTime());
		//g_lightPos.z = 3.0f * cos(glfwGetTime());

		// Set background color to black
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 0.5f);							// Black Background					
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


		// Draw our objects
		G_light.generateLight(G_camera.getViewMatrix(), g_lightPos, G_camera.mView);

		// Transformation matrices
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)g_windowSizeX / (float)g_windowSizeY, 0.1f, 100.0f);
		glm::mat4 view = G_camera.getViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);

		// ATAT
		G_atat.atatShader = atatShader;
		G_atat.atatShader.use();
		G_atat.atatShader.setMat4("projection", projection);
		G_atat.atatShader.setMat4("view", view);
		G_atat.atatShader.setMat4("model", model);
		G_atat.redrawATAT();
		//G_atat.initialDraw(G_camera.getViewMatrix(), g_lightPos, G_camera.mView);

		

		// Landscape
		G_scape.landscapeShader = landscapeShader;
		G_scape.landscapeShader.use();
		G_scape.landscapeShader.setMat4("projection", projection);
		G_scape.landscapeShader.setMat4("view", view);
		G_scape.landscapeShader.setMat4("model", model);
		G_scape.landscapeShader.setVec3("light.position", g_flPosition);
		G_scape.landscapeShader.setVec3("light.direction", g_flDirection);
		G_scape.landscapeShader.setVec3("light.color", 1.0f, 1.0f, 1.0f);
		G_scape.landscapeShader.setFloat("light.cutOff", glm::cos(glm::radians(g_cutOffAngle)));
		G_scape.landscapeShader.setFloat("light.outerCutOff", glm::cos(glm::radians(g_outerCutOffAngle)));
		G_scape.drawLandscape(G_camera.getViewMatrix(), g_lightPos, G_camera.mView);

		if (g_toggleNormalVectors) {

			// Draw normal vectors of ATAT
			G_atat.atatShader = normalDrawShader;
			G_atat.atatShader.use();
			G_atat.atatShader.setMat4("projection", projection);
			G_atat.atatShader.setMat4("view", view);
			G_atat.atatShader.setMat4("model", model);
			G_atat.redrawATAT();
			//G_atat.initialDraw(G_camera.getViewMatrix(), g_lightPos, G_camera.mView);

			// Draw normal vectors of Landscape
			G_scape.landscapeShader = normalDrawShader;
			G_scape.landscapeShader.use();
			G_scape.landscapeShader.setMat4("projection", projection);
			G_scape.landscapeShader.setMat4("view", view);
			G_scape.landscapeShader.setMat4("model", model);
			G_scape.drawLandscape(G_camera.getViewMatrix(), g_lightPos, G_camera.mView);
		}

		

		// Skybox
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

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {

		g_toggleNormalVectors = !g_toggleNormalVectors;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {

		G_atat.changeAnimateValues();
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {


	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {

		G_atat.sidewardRotation++;
		G_atat.changeRotation();
	}
	else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {

		G_atat.sidewardRotation--;
		std::cout << "Right key pressed. Rotation: " << G_atat.sidewardRotation << std::endl;
		G_atat.changeRotation();
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

