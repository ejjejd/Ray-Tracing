#pragma once

#include "shape.h"

struct Plane : public Shape
{
	glm::vec3 Position;
	glm::vec3 PNormal;

	Plane()
	{

	}

	Plane(const glm::vec3 position, const glm::vec3 normal, const ::Material material)
	{
		Position = position;
		PNormal = normal;
		Material = material;
	}

	bool Intersection(const Ray ray, float& distance) const override
	{
		float denom = glm::dot(ray.Direction, PNormal);

		if (abs(denom) < 1e-6f)
			return false;

		float result = glm::dot((Position - ray.Origin), PNormal / denom);
		distance = result;

		return distance >= 0.0f;
	}

	glm::vec3 Normal(const glm::vec3 point) const override
	{
		return PNormal;
	}
};