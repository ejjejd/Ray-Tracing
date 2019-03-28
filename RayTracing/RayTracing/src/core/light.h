#pragma once

#include "glm/glm.hpp"

struct Light
{
	glm::vec3 Position;
	float Intensity;

	Light()
	{
		Intensity = 0.0f;
	}

	Light(const glm::vec3 position, const float intensity)
	{
		Position = position;
		Intensity = intensity;
	}
};