#include "BVH.h"

import std;

BVH bvh;  // Global BVH object

void UpdateNodeBounds(uint32_t nodeIndex, const Scene& scene);

void Subdivide(uint32_t nodeIndex, const Scene& scene)
{
	// terminate recursion
	BVHNode& node = bvh.nodes[nodeIndex];
	if (node.numPrims <= 2) return;
	// determine split axis and position
	glm::vec3 extent = node.aabbMax - node.aabbMin;
	int axis = 0;
	if (extent.y > extent.x) axis = 1;
	if (extent.z > extent[axis]) axis = 2;
	float splitPos = node.aabbMin[axis] + extent[axis] * 0.5f;
	// in-place partition
	int i = node.leftFirst;
	int j = i + node.numPrims - 1;
	while (i <= j)
	{
		if (scene.tris[bvh.triIdx[i]].centroid[axis] < splitPos)
			i++;
		else
			std::swap(bvh.triIdx[i], bvh.triIdx[j--]);
	}
	// abort split if one of the sides is empty
	int leftCount = i - node.leftFirst;
	if (leftCount == 0 || leftCount == node.numPrims) return;
	// create child nodes
	int leftChildIdx = bvh.nodesUsed++;
	int rightChildIdx = bvh.nodesUsed++;
	bvh.nodes[leftChildIdx].leftFirst = node.leftFirst;
	bvh.nodes[leftChildIdx].numPrims = leftCount;
	bvh.nodes[rightChildIdx].leftFirst = i;
	bvh.nodes[rightChildIdx].numPrims = node.numPrims - leftCount;
	node.leftFirst = leftChildIdx;
	node.numPrims = 0;
	UpdateNodeBounds(leftChildIdx, scene);
	UpdateNodeBounds(rightChildIdx, scene);
	// recurse
	Subdivide(leftChildIdx, scene);
	Subdivide(rightChildIdx, scene);
}

void UpdateNodeBounds(uint32_t nodeIndex, const Scene& scene)
{
	BVHNode& node{ bvh.nodes[nodeIndex] };
	node.aabbMin = glm::vec3(1e30f);  // Initialize to a large value
	node.aabbMax = glm::vec3(-1e30f);  // Initialize to a small value
	auto& tris{ scene.tris };
	for (uint32_t first{ node.leftFirst }, i{ 0 }; i < node.numPrims; ++i)
	{
		uint32_t leafTriIdx = bvh.triIdx[first + i];  // Get the triangle index from the BVH
		const Tri& tri = tris[leafTriIdx];
		node.aabbMin = glm::min(node.aabbMin, tri.vertex0);
		node.aabbMin = glm::min(node.aabbMin, tri.vertex1);
		node.aabbMin = glm::min(node.aabbMin, tri.vertex2);
		node.aabbMax = glm::max(node.aabbMax, tri.vertex0);
		node.aabbMax = glm::max(node.aabbMax, tri.vertex1);
		node.aabbMax = glm::max(node.aabbMax, tri.vertex2);
	}
}

void BuildBVH(const Scene& scene)
{
	const uint32_t numTris = scene.getNumTris();
	//intialize the BVH
	for (uint32_t i{ 0 }; i < numTris; ++i)
	{
		bvh.triIdx[i] = i;  // Initialize the triangle indices in the BVH
	}

	auto& tris{ scene.tris };

	//assign all triangles to the root node
	BVHNode& rootNode = bvh.nodes[bvh.rootNodeIndex];
	rootNode.leftFirst = 0;
	rootNode.numPrims = numTris;

	UpdateNodeBounds(bvh.rootNodeIndex, scene);
	// Start subdividing the root node
	Subdivide(bvh.rootNodeIndex, scene);
}

const BVH& GetBVH()
{
	return bvh;  // Return the global BVH object
}

