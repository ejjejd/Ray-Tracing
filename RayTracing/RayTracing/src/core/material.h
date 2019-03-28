#pragma once

#include "glm/glm.hpp"

struct Material
{
	glm::vec3 Diffuse;
	glm::vec3 Albedo;
	float Shininess;

	Material()
	{
		Shininess = 0.0f;
	}

	Material(const glm::vec3 diffuse)
	{
		Diffuse = diffuse;
		Shininess = 0.0f;
	}

	Material(const glm::vec3 diffuse, const glm::vec3 albedo, const float shininess)
	{
		Diffuse = diffuse;
		Albedo = albedo;
		Shininess = shininess;
	}
};