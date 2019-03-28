#pragma once

#include "../ray.h"
#include "../material.h"
#include "../light.h"
#include "../../shapes/shape.h"

#include <vector>

glm::vec3 environmentColor = glm::vec3(0.5f, 0.7f, 0.8f);

struct Hit
{
	glm::vec3 point;
	glm::vec3 normal;
	Material material;
};

bool SceneIntersection(const Ray ray, const std::vector<Shape*> shapes, Hit& hit)
{
	float distance = INFINITY;

	for (int i = 0; i < shapes.size(); ++i)
	{
		float tempDist;

		if (shapes[i]->Intersection(ray, tempDist) && tempDist < distance)
		{
			distance = tempDist;

			hit.point = ray.PointAt(distance);
			hit.normal = glm::normalize(shapes[i]->Normal(hit.point));
			hit.material = shapes[i]->Material;
		}
	}

	return distance < 1000.0f;
}

glm::vec3 CastRay(const Ray ray, const std::vector<Shape*> shapes, std::vector<Light> lights)
{
	Hit hit;

	if (!SceneIntersection(ray, shapes, hit))
		return environmentColor;

	glm::vec3 diffuse;
	glm::vec3 lighDir;

	for (int i = 0; i < lights.size(); ++i)
	{
		lighDir = glm::normalize(lights[i].Position - hit.point);

		diffuse = hit.material.Diffuse * (lights[i].Intensity * glm::max(0.0f, glm::dot(lighDir, hit.normal)));
	}

	return diffuse;
}