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

glm::mat4 Camera::getWorldToViewMatrix() const
{
	return glm::lookAt(position, position + viewDirection, UP);
}

