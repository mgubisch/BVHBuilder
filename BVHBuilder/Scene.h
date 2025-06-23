#pragma once

#include "math.h"

constexpr uint32_t NUM_TRIS = 64;

struct BHVNode;

class Scene
{
public:
	Scene();

	//the original scene
	Tri tris[NUM_TRIS];
	 //this will be modifed by the BVH builder to sort the triangles

	constexpr uint32_t getNumTris() const
	{
		return NUM_TRIS;
	}
};

