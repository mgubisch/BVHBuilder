#include "Scene.h"

Scene::Scene()
{
	for (int i{ 0 }; i < NUM_TRIS; ++i)
	{

		glm::vec3 r0(RandomFloat(), RandomFloat(), RandomFloat());
		glm::vec3 r1(RandomFloat(), RandomFloat(), RandomFloat());
		glm::vec3 r2(RandomFloat(), RandomFloat(), RandomFloat());
		tris[i].vertex0 = r0 * 9.0f - glm::vec3(5.0f);
		tris[i].vertex1 = tris[i].vertex0 + r1;
		tris[i].vertex2 = tris[i].vertex0 + r2;
		tris[i].centroid = (tris[i].vertex0 + tris[i].vertex1 + tris[i].vertex2) * 0.3333f;
	}
}
