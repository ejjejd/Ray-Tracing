#pragma once

#include <vector>

#include "glm/glm.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image_read.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

struct Image
{
	std::vector<glm::vec3> Data;
	int Width;
	int Height;
};

Image LoadImage(const char* filepath)
{
	Image result;

	int n = -1;
	unsigned char* pixmap = stbi_load("res/env.jpg", &result.Width, &result.Height, &n, 0);

	if (!pixmap || n != 3)
		abort();

	result.Data = std::vector<glm::vec3>(result.Width * result.Height);

	for (int j = result.Height - 1; j >= 0; j--) {
		for (int i = 0; i < result.Width; i++) {
			result.Data[i + j * result.Width] = glm::vec3(pixmap[(i + j * result.Width) * 3 + 0], pixmap[(i + j * result.Width) * 3 + 1], pixmap[(i + j * result.Width) * 3 + 2]) * (1 / 255.0f);
		}
	}

	stbi_image_free(pixmap);

	return result;
}

void SaveImageJPG(const char* filepath, const int width, const int height, const std::vector<glm::vec3> buffer)
{
	std::vector<unsigned char> img(width * height * 3);

	for (int i = 0; i < width * height; ++i)
	{
		glm::vec3 c = buffer[i];

		float max = glm::max(c[0], glm::max(c[1], c[2]));

		if (max > 1)
			c = c * (1.0f / max);

		for (int j = 0; j < 3; ++j)
			img[i * 3 + j] = (unsigned char)(255.0f * glm::max(0.0f, glm::min(1.0f, buffer[i][j])));
	}

	stbi_write_jpg(filepath, width, height, 3, img.data(), 100.0f);
}

void SaveImageBMP(const char* filepath, const int width, const int height, const std::vector<glm::vec3> buffer)
{
	std::vector<unsigned char> img(width * height * 3);

	for (int i = 0; i < width * height; ++i)
	{
		glm::vec3 c = buffer[i];

		float max = glm::max(c[0], glm::max(c[1], c[2]));

		if (max > 1)
			c = c * (1.0f / max);

		for (int j = 0; j < 3; ++j)
			img[i * 3 + j] = (unsigned char)(255.0f * glm::max(0.0f, glm::min(1.0f, buffer[i][j])));
	}

	stbi_write_bmp(filepath, width, height, 3, img.data());
}

void SaveImagePPM(const char* filepath, const int width, const int height, const std::vector<glm::vec3> buffer)
{
	std::ofstream out(filepath, std::ios::binary);
	out << "P6\n" << width << ' ' << height << "\n255\n";

	for (int i = 0; i < width * height; ++i)
	{
		for (int j = 0; j < 3; ++j)
			out << (unsigned char)(glm::max(0.0f, glm::min(1.0f, buffer[i][j])) * 255.0f);
	}
}