#pragma once

#include "ray.h"
#include "glm/glm.hpp"

class Camera
{
private:
	glm::vec3 Position;
	glm::vec2 Resolution;
	float AspectRatio;
	float FOV;
public:
	Camera()
	{
		AspectRatio = 0.0f;
		FOV = 0.0f;
	}

	Camera(const glm::vec3 position, const int width, const int height, const float fov)
	{
		Position = position;
		Resolution = glm::vec2(width, height);
		AspectRatio = Resolution.x / Resolution.y;
		FOV = glm::tan(fov / 2.0f);
	}

	Ray GetRay(const int ix, const float iy)
	{
		float u = (2.0f * (ix + 0.5f) / Resolution.x - 1) * FOV * AspectRatio;
		float v = -(2.0f * (iy + 0.5f) / Resolution.y - 1) * FOV;

		return Ray(Position, glm::normalize(glm::vec3(u, v, -1.0f)));
	}
};