#pragma once

#include "math.h"
#include "Scene.h"

struct BVHNode
{
	glm::vec3 aabbMin;  // Minimum bounds of the node
	glm::vec3 aabbMax;  // Maximum bounds of the node
	uint32_t leftFirst; // Index of the left child node if it is not a leaf or the first triangle index if it is a leaf
	uint32_t numPrims; // Number of triangles in this node (if it is a leaf)

	constexpr bool isLeaf() const
	{
		return numPrims > 0;
	}
};

struct BVH
{
	uint32_t triIdx[NUM_TRIS];
	BVHNode  nodes[NUM_TRIS * 2 - 1];  // Pointer to the array of BVH nodes
	uint32_t rootNodeIndex{0};  // Index of the root node
	uint32_t nodesUsed{1};  // Number of nodes currently used in the BVH
};

void BuildBVH(const Scene& scene);

const BVH& GetBVH();