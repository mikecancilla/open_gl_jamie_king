#pragma once

#include <glm.hpp>

class Camera
{
	glm::vec3 position;
	glm::vec3 viewDirection; // Needs to be normalized (a unit vector)
	const glm::vec3 UP;
	glm::vec2 oldMousePosition;

public:
	Camera();
	virtual ~Camera();

	void mouseUpdate(const glm::vec2 &newMousePosition);
	glm::mat4 getWorldToViewMatrix() const;
};

