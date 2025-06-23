#include "Renderer.h"
#include <cassert>

#include "math.h"
#include "Timer.h"
#include "Scene.h"
#include "BVH.h"

//Runtimes
//brute force intersection triangles with 640x640 pixels: NUM_TRIS = 64   Render: ~96ms   BVHBuild: 0ms
//brute force intersection triangles with 640x640 pixels: NUM_TRIS = 512  Render: ~1109ms BVHBuild: 0ms
//brute force intersection triangles with 640x640 pixels: NUM_TRIS = 1024 Render: ~2980ms BVHBuild: 0ms

//simple bvh build and traversal with 640x640 pixels: NUM_TRIS = 64   Render: ~19ms BVHBuild: 0.005ms
//simple bvh build and traversal with 640x640 pixels: NUM_TRIS = 512  Render: ~60ms BVHBuild: 0.069ms
//simple bvh build and traversal with 640x640 pixels: NUM_TRIS = 1024 Render: ~93ms BVHBuild: 0.142ms
//simple bvh build and traversal with 640x640 pixels: NUM_TRIS = 12582 Render: ~225ms BVHBuild: 1.486ms


import std;

Timer timer;  /* global timer to measure frame time. */

void IntersectBVH(Ray& ray, const Scene& scene, const BVH& bvh, uint32_t nodeIndex = 0)
{
	const BVHNode& node = bvh.nodes[nodeIndex];

	if (!IntersectAABB(ray, node.aabbMin, node.aabbMax))
		return;

	if (node.isLeaf())
	{
		for (uint32_t i{ 0 }; i < node.numPrims; ++i)
		{
			IntersectTri(ray, scene.tris[bvh.triIdx[node.leftFirst + i]]);  /* check if the ray intersects with the triangle. */
		}
	}
	else
	{
		IntersectBVH(ray, scene, bvh, node.leftFirst);  /* recursively check the left child node. */
		IntersectBVH(ray, scene, bvh, node.leftFirst + 1);  /* recursively check the right child node. */
	}

}

void Renderer::Init(SDL_Window* window)
{
	assert(window != nullptr && "Renderer surface cannot be null");
	m_window = window;
	m_surface = SDL_GetWindowSurface(m_window);
	assert(m_surface != nullptr && "Renderer surface cannot be null");
}

void Renderer::Render(Scene& scene)
{
	timer.reset();  /* reset the timer at the start of each frame. */
	
	//render triangles
	Ray ray;
	const auto width{ m_surface->w };
	const auto height{ m_surface->h };
	for(int y{ 0 }; y < height; ++y)
	{
		for (int x{ 0 }; x < width; ++x)
		{
			glm::vec3 pixelPos = p0 + (p1 - p0) * (static_cast<float>(x) / static_cast<float>(width)) + (p2 - p0) * (static_cast<float>(y) / static_cast<float>(height));
			ray.Origin = m_cameraPos;  /* set the ray origin to the camera position. */
			ray.Direction = glm::normalize(pixelPos - m_cameraPos);  /* set the ray direction to the pixel position minus the camera position. */
			ray.t = 1e30f;  /* reset the ray t value to a large value. */

#if 0
			for(int i{ 0 }; i < NUM_TRIS; ++i)
			{
				IntersectTri(ray, scene.tris[i]);  /* check if the ray intersects with the triangle. */
			}
#else
			IntersectBVH(ray, scene, GetBVH());  /* check if the ray intersects with the BVH. */
#endif
			if (ray.t < 1e30f)  /* if the ray intersects with the triangle, draw it. */
			{
				uint8_t c = 255 - (int)(ray.t * 40);
				SDL_WriteSurfacePixel(m_surface, x, y, c, c, c, c);  /* draw the pixel with a random color. */
			}
		}
		
	}


	auto elapsed = timer.elapsed();  /* get the elapsed time for this frame. */
	SDL_Log("Frame time: %.3f ms", elapsed * 1000.0f);  /* log the frame time in milliseconds. */
}

void Renderer::Clear()
{
	if (!SDL_FillSurfaceRect(m_surface, nullptr, SDL_MapSurfaceRGB(m_surface, 0x00, 0x00, 0x00)))  /* fill the surface with black. */
	{
		SDL_Log("Couldn't fill surface: %s", SDL_GetError());
	}
}

void Renderer::Present()
{
	SDL_UpdateWindowSurface(m_window);  /* update the window surface to show the changes. */
}

void Renderer::Shutdown()
{
	//nothing to do here for now
}
