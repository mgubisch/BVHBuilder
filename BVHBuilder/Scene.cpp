#include "Scene.h"

import std;

Scene::Scene()
{
#if USE_TESTFILE

    FILE* file = fopen("../../test.tri", "r");
    float a, b, c, d, e, f, g, h, i;
    for (int t = 0; t < NUM_TRIS; t++)
    {
        fscanf(file, "%f %f %f %f %f %f %f %f %f\n",
            &a, &b, &c, &d, &e, &f, &g, &h, &i);
        tris[t].vertex0 = glm::vec3(a, b, c);
        tris[t].vertex1 = glm::vec3(d, e, f);
        tris[t].vertex2 = glm::vec3(g, h, i);
        tris[t].centroid = (tris[t].vertex0 + tris[t].vertex1 + tris[t].vertex2) * 0.3333f;
    }
    fclose(file);
#else 
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
#endif 
}
