#pragma once

#include "math.h"

#define USE_TESTFILE 1

#if USE_TESTFILE
constexpr uint32_t NUM_TRIS = 12582; //testfile contains 12582 triangles
#else
constexpr uint32_t NUM_TRIS = 64; //testfile contains 64 triangles, for testing purposes
#endif

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

