#include "Camera.h"
#include <gtx\transform.hpp>

Camera::Camera()
	: viewDirection(0, 0, -1)
	, UP(0, 1, 0)
{
}

Camera::~Camera()
{
}

void Camera::mouseUpdate(const glm::vec2 & newMousePosition)
{
	glm::vec2 mouseDelta = newMousePosition - oldMousePosition;

	if(glm::length(mouseDelta) > 50.f)
	{
		oldMousePosition = newMousePosition;
		return;
	}

	const float ROTATIONAL_SPEED = 128.f;

	// For a vertical camera rotation, you currently have a look direction and and up, these are 90 degrees from each other.
	// Take the cross product of the view and up, to get a perpendicular vector to the right
	// Rotate up or down around this perpendicular cross product result vector
	glm::vec3 toRotateAround = glm::cross(viewDirection, UP);

	glm::mat4 rotator = glm::rotate(-mouseDelta.x / ROTATIONAL_SPEED, UP) *
		                glm::rotate(-mouseDelta.y / ROTATIONAL_SPEED, toRotateAround); // Rotate in X and Y in one step now

    // Update the Y rotation
	viewDirection = glm::mat3(rotator) * viewDirection;

	// 1 degree per mouse pixel, update the X rotation
	//viewDirection = glm::mat3(glm::rotate(-mouseDelta.x / ROTATIONAL_SPEED, UP)) * viewDirection;

	// Update the Y rotation
	//viewDirection = glm::mat3(glm::rotate(-mouseDelta.y / ROTATIONAL_SPEED, toRotateAround)) * viewDirection;

	oldMousePosition = newMousePosition;
}

glm::mat4 Camera::getWorldToViewMatrix() const
{
	return glm::lookAt(position, position + viewDirection, UP);
}
