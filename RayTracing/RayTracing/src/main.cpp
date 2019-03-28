#define _USE_MATH_DEFINES
#include <math.h>

#include <fstream>
#include <vector>

#include "shapes/sphere.h"

#include "core/camera.h"
#include "core/render/cast_ray.h"

#define WIDTH	400
#define HEIGHT	200

void Render()
{
	Material ivory(glm::vec3(0.4f, 0.4f, 0.3f));
	Material red(glm::vec3(0.5f, 0.1f, 0.1f));
	Material green(glm::vec3(0.1f, 0.5f, 0.1f));

	std::vector<Shape*> shapes
	{
		(new Sphere(glm::vec3(0.0f, 0.0f, -75.0f), 0.5f, ivory)),
		(new Sphere(glm::vec3(-1.1f, -0.3f, -85.0f), 0.3f, red)),
		(new Sphere(glm::vec3(1.1f, -0.3f, -85.0f), 0.4f, green))
	};

	std::vector<Light> lights
	{
		Light(glm::vec3(6.0f, 6.0f, 15.0f), 1.0f),
		Light(glm::vec3(-6.0f, 20.0f, 15.0f), 1.0f),
		Light(glm::vec3(0.0f, 20.0f, 15.0f), 1.5f)
	};

	Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), WIDTH, HEIGHT, M_PI / 2.0f);

	std::ofstream out("out.ppm", std::ios::binary);
	out << "P6\n" << WIDTH << ' ' << HEIGHT << "\n255\n";

	glm::vec3 pixel;

	for (int j = 0; j < HEIGHT; ++j)
	{
		for (int i = 0; i < WIDTH; ++i)
		{
			pixel = CastRay(camera.GetRay(i, j), shapes, lights);

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