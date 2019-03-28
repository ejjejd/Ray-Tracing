#define _USE_MATH_DEFINES
#include <math.h>

#include <fstream>
#include <vector>

#include "shapes/sphere.h"

#include "core/camera.h"

#define WIDTH	400
#define HEIGHT	200

void Render()
{
	Material ivory(glm::vec3(0.4f, 0.4f, 0.3f));

	Sphere sphere(glm::vec3(0.0f, 0.0f, -50.0f), 0.5f, ivory);

	Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), WIDTH, HEIGHT, M_PI / 2.0f);

	std::ofstream out("out.ppm", std::ios::binary);
	out << "P6\n" << WIDTH << ' ' << HEIGHT << "\n255\n";

	glm::vec3 pixel;

	float t;

	for (int j = 0; j < HEIGHT; ++j)
	{
		for (int i = 0; i < WIDTH; ++i)
		{
			pixel = glm::vec3(0.5f, 0.7f, 0.8f);

			if (sphere.Intersection(camera.GetRay(i, j), t))
				pixel = sphere.Material.Diffuse;

			for (int t = 0; t < 3; ++t)
				out << (unsigned char)(glm::max(0.0f, glm::min(1.0f, pixel[t])) * 255.0f);
		}
	}
}

int main()
{
	Render();

	return(0);
}