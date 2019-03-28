#pragma once

#include "../core/material.h"
#include "../core/ray.h"

struct Shape
{
	Material Material;

	virtual bool Intersection(const Ray ray, float& distance) const = 0;
	virtual glm::vec3 Normal(const glm::vec3 point) const = 0;
};