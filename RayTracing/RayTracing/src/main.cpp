#define _USE_MATH_DEFINES
#include <math.h>

#include <fstream>
#include <vector>

#include "shapes/sphere.h"
#include "shapes/plane.h"

#include "core/camera.h"
#include "core/render/cast_ray.h"

#include "image.h"

#define WIDTH	1920
#define HEIGHT	1080

void Render()
{
	Material ivory(glm::vec3(0.4f, 0.4f, 0.3f), glm::vec3(0.6, 0.3, 0.2), 50.0f);
	Material red(glm::vec3(0.5f, 0.1f, 0.1f), glm::vec3(0.9f, 0.0f, 0.0f), 10.0f);
	Material green(glm::vec3(0.1f, 0.5f, 0.1f), glm::vec3(0.6, 0.3, 0.2), 50.0f);
	Material mirror(glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.0, 10.0, 0.8), 1425.0f);
	Material plane(glm::vec3(0.231, 0.243, 0.329), glm::vec3(0.9f, 0.1f, 0.1f), 10.0f);

	Material test(glm::vec3(0.4, 0.4, 0.3), glm::vec3(0.0, 0.3, 0.0), 0.0f);

	std::vector<Shape*> shapes
	{
		(new Sphere(glm::vec3(0.0f, -4.0f, -25.0f), 5.5f, ivory)),
		(new Sphere(glm::vec3(11.0f, -5.5f, -25.0f), 4.0f, green)),
		(new Sphere(glm::vec3(-11.0f, -5.5f, -25.0f), 4.0f, red)),
		(new Sphere(glm::vec3(0.0f, 7.0f, -30.0f), 3.0f, mirror)),
		(new Plane(glm::vec3(0.0f, -10.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), plane))
	};

	std::vector<Light> lights
	{
		Light(glm::vec3(-20, 20, 20), 1.0),
		Light(glm::vec3(30, 50, -25), 1.0),
		Light(glm::vec3(30, 20, 30), 1.0)
	};

	Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), WIDTH, HEIGHT, M_PI / 2.0f);

	std::vector<glm::vec3> frameBuffer(WIDTH * HEIGHT);

	for (int j = 0; j < HEIGHT; ++j)
	{
		for (int i = 0; i < WIDTH; ++i)
		{
			frameBuffer[i + j * WIDTH] = CastRay(camera.GetRay(i, j), shapes, lights);
		}
	}

	SaveImageJPG("out.jpg", WIDTH, HEIGHT, frameBuffer);
}

int main()
{
	Image img = LoadImage("res/env.jpg");
	evironment = img;
	 
	Render();

	return(0);
}