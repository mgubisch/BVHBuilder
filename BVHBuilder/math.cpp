#include "math.h"

//https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
void IntersectTri(Ray& ray, const Tri& tri)
{
	using namespace glm;
	const vec3 edge1 = tri.vertex1 - tri.vertex0;
	const vec3 edge2 = tri.vertex2 - tri.vertex0;
	const vec3 h = cross(ray.Direction, edge2);
	const float a = dot(edge1, h);
	if (a > -1e-8f && a < 1e-8f) {
		return;  // Ray is parallel to the triangle
	}
	const float f = 1.0f / a;
	const vec3 s = ray.Origin - tri.vertex0;
	const float u = f * dot(s, h);
	if (u < 0.0f || u > 1.0f) {
		return;  // Intersection is outside the triangle
	}
	const vec3 q = cross(s, edge1);
	const float v = f * dot(ray.Direction, q);
	if (v < 0.0f || u + v > 1.0f) {
		return;  // Intersection is outside the triangle
	}
	const float t = f * dot(edge2, q);
	if (t > 1e-8f && t < ray.t) {
		ray.t = t;  // Update the ray's t value if intersection occurs
	}
}
