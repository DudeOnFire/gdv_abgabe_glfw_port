#pragma once

//------------- Includes ----------------
#include <glad/glad.h>
#include "Include/glm/glm.hpp"
#include "Include/glm/gtc/matrix_transform.hpp"
#include "Include/glm/gtc/type_ptr.hpp"

#include <iostream>

// Enum for possible camera directions
enum CamDir {

	UP,
	DOWN,
	LEFT,
	RIGHT
};


// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 4.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


class Camera
{
public:

	// Define camera vectors 
	glm::vec3 mView; // The point the camera is looking at ->front
	glm::vec3 mUp; //world up
	glm::vec3 mDirection; // Direction vector of camera, normalized result of mPosition - mView
	glm::vec3 mPosition; // In scene position
	glm::vec3 mRight;	// Vector that is perpendicular to mView and mUp

	// Pitch and yaw values
	float pitch;
	float yaw;
	float mouseSensitivity;


	Camera(glm::vec3 pos, glm::vec3 up);
	glm::mat4 getViewMatrix() { return glm::lookAt(mPosition, mPosition + mView, mUp); }
	void handleMouseInput(float xoffset, float yoffset, GLboolean constrainPitch);
	void handleKeyboardInput(CamDir dir, float delta_time);
	void outputmView() { std::cout << "mView: (" << mView.x << ";" << mView.y << ";" << mView.z << ")" << std::endl; }
	void outputmPosition() { std::cout << "mPosition: (" << mPosition.x << ";" << mPosition.y << ";" << mPosition.z << ")" << std::endl; }
	void outputmUp() { std::cout << "mUp: (" << mUp.x << ";" << mUp.y << ";" << mUp.z << ")" << std::endl; }

private:
	void updateCameraVectors();

};
