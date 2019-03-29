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

glm::vec3 CastRay(const Ray ray, const std::vector<Shape*> shapes, std::vector<Light> lights, const int depth = 0)
{
	Hit hit;

	if (depth > 4 || !SceneIntersection(ray, shapes, hit))
		return environmentColor;

	Ray reflectRay;
	reflectRay.Direction = glm::normalize(glm::reflect(ray.Direction, hit.normal));
	reflectRay.Origin = glm::dot(reflectRay.Direction, hit.normal) < 0.0f ? hit.point - hit.normal * 1e-3f : hit.point + hit.normal * 1e-3f;

	glm::vec3 reflectColor = CastRay(reflectRay, shapes, lights, depth + 1);

	float diffuse = 0.0f;
	float specular = 0.0f;

	glm::vec3 lightDir;
	float lightDistance = 0.0f;

	Ray shadowRay;
	Hit shadowHit;

	for (int i = 0; i < lights.size(); ++i)
	{
		lightDir = glm::normalize((lights[i].Position - hit.point));
		lightDistance = glm::length(lights[i].Position - hit.point);

		shadowRay.Origin = glm::dot(lightDir, hit.normal) < 0.0f ? hit.point - hit.normal * 1e-3f : hit.point + hit.normal * 1e-3f;
		shadowRay.Direction = lightDir;

		if (SceneIntersection(shadowRay, shapes, shadowHit) && glm::length(shadowHit.point - shadowRay.Origin) < lightDistance)
			continue;


		diffuse += lights[i].Intensity * glm::max(0.0f, glm::dot(lightDir, hit.normal));
		specular += powf(glm::max(0.0f, glm::dot(-glm::reflect(-lightDir, hit.normal), ray.Direction)), hit.material.Shininess) * lights[i].Intensity;
	}

	return hit.material.Diffuse * diffuse * hit.material.Albedo[0] + glm::vec3(1.0f, 1.0f, 1.0f) * specular * hit.material.Albedo[1] + reflectColor * hit.material.Albedo[2];
}