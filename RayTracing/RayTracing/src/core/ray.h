#pragma once

#include "glm/glm.hpp"

struct Ray
{
	glm::vec3 Origin;
	glm::vec3 Direction;

	Ray()
	{

	}

	Ray(const glm::vec3 origin, const glm::vec3 direction)
	{
		Origin = origin;
		Direction = direction;
	}

	glm::vec3 PointAt(const float distance) const
	{
		return Origin + Direction * distance;
	}
};