#pragma once

#include <glm/glm.hpp>
#include <cstdlib>

struct Tri
{
	glm::vec3 vertex0;
	glm::vec3 vertex1;
	glm::vec3 vertex2;
	glm::vec3 centeroid;
};

struct Ray
{
	glm::vec3 Origin;
	glm::vec3 Direction;
	float t = 1e30f;
};

inline [[nodiscard]] float RandomFloat(float min, float max)
{
	return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

inline [[nodiscard]] float RandomFloat()
{
	return static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
}


void IntersectTri(Ray& ray, const Tri& tri);