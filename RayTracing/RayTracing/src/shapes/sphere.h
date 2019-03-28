#pragma once

#include "shape.h"

struct Sphere : public Shape
{
	glm::vec3 Center;
	float Radius;

	Sphere()
	{
		Radius = 0.0f;
	}

	Sphere(const glm::vec3 center, const float radius, const ::Material material)
	{
		Center = center;
		Radius = radius;
		Material = material;
	}

	bool Intersection(const Ray ray, float& distance) const override
	{
		glm::vec3 L = Center - ray.Origin;
		float tca = glm::dot(L, ray.Direction);

		float s2 = glm::dot(L, L) - tca * tca;
		float s = sqrt(s2);

		if (s > Radius)
			return false;

		float thc = sqrt(Radius * Radius - s2);
		
		distance = tca - thc;
		float distance1 = tca + thc;

		if (distance < 0.0f)
			distance = distance1;
		if (distance1 < 0.0f)
			return false;

		return true;
	}

	glm::vec3 Normal(const glm::vec3 point) const override
	{
		return point - Center;
	}
};