#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	glm::vec3 position{ 0.0f, 1.8f, 140.0f };
	float yaw = -90.0f; 
	float pitch = 0.0f;
	float fov = 45.0f;
	float nearPoint = 0.1f;
	float farPoint = 1000.0f;

	glm::mat4 getView() const
	{
		glm::vec3 forward;
		forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		forward.y = sin(glm::radians(pitch));
		forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		return glm::lookAt(position, position + glm::normalize(forward), { 0.0f, 1.0f, 0.0f });
	}

	glm::mat4 getProjection(float aspect) const
	{
		return glm::perspective(glm::radians(fov), aspect, nearPoint, farPoint);
	}
};
