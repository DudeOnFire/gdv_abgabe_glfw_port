#include "Camera.h"


Camera::Camera(glm::vec3 pos, glm::vec3 up) : mView(glm::vec3(0.0, 0.0, 0.0))
{

	mPosition = pos;
	mUp = up;

	yaw = -90.0f;
	pitch = 0.0f;
	mPosition = pos;
	mUp = up;
	updateCameraVectors();
}


void Camera::handleKeyboardInput(CamDir dir, float delta_time)
{
	float v = SPEED * delta_time;

	if (dir == UP) {
		mPosition += mView * v;
	}
	else if (dir == DOWN) {
		mPosition -= mView * v;
	}
	else if (dir == LEFT) {
		mPosition -= glm::normalize(glm::cross(mView, mUp)) * v;
	}
	else if (dir == RIGHT) {
		mPosition += glm::normalize(glm::cross(mView, mUp)) * v;
	}
}

void Camera::handleMouseInput(float xoffset, float yoffset, GLboolean constrainPitch = true) {

	// Multiply with sensitivity
	xoffset *= SENSITIVITY;
	yoffset *= SENSITIVITY;

	// Add calculated offset to camera pitch and yaw
	yaw += xoffset;
	pitch += yoffset;

	// Set constraints so the camera can't move more than 180 degrees total in the vertical direction
	if (constrainPitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	// Inform user
	std::cout << "Mouse moved" << std::endl;
	outputmPosition();
	outputmView();

	// Update Front, Right and Up vectors
	updateCameraVectors();
}

void Camera::updateCameraVectors() {

	// Calculate new view vector
	glm::vec3 front;
	front.x = cos(glm::radians(YAW)) * cos(glm::radians(PITCH));
	front.y = sin(glm::radians(PITCH));
	front.z = sin(glm::radians(YAW)) * cos(glm::radians(PITCH));
	mView = glm::normalize(front);

	// Recalculate up and right vector
	mRight = glm::normalize(glm::cross(mView, mUp));
	mUp = glm::normalize(glm::cross(mRight, mView));
}