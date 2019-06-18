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

	// 1 degree per mouse pixel
	viewDirection = glm::mat3(glm::rotate(-mouseDelta.x / 64.f, UP)) * viewDirection;

	oldMousePosition = newMousePosition;
}

glm::mat4 Camera::getWorldToViewMatrix() const
{
	return glm::lookAt(position, position + viewDirection, UP);
}
