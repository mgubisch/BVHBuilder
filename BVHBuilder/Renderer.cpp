#include "Renderer.h"
#include <cassert>

#include "math.h"

//Runtimes
//brute force intersection of 64 triangles with 640x640 pixels: Render: ~96ms BVHBuild: 0ms

import std;

// timer
struct Timer
{	
	Timer() { reset(); }
	float elapsed() const
	{
		using namespace std;
		chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
		chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - start);
		return (float)time_span.count();
	}
	void reset() { start = std::chrono::high_resolution_clock::now(); }
	std::chrono::high_resolution_clock::time_point start;
};

Timer timer;  /* global timer to measure frame time. */

//todo: move this to a separate file
constexpr size_t NUM_TRIS = 64;
Tri tri[NUM_TRIS];

void create_scene()
{
	for (int i{0}; i < NUM_TRIS; ++i)
	{

		glm::vec3 r0(RandomFloat(), RandomFloat(), RandomFloat());
		glm::vec3 r1(RandomFloat(), RandomFloat(), RandomFloat());
		glm::vec3 r2(RandomFloat(), RandomFloat(), RandomFloat());
		tri[i].vertex0 = r0 * 9.0f - glm::vec3(5.0f);
		tri[i].vertex1 = tri[i].vertex0 + r1;
		tri[i].vertex2 = tri[i].vertex0 + r2;
	}
}


void Renderer::Init(SDL_Window* window)
{
	assert(window != nullptr && "Renderer surface cannot be null");
	m_window = window;
	m_surface = SDL_GetWindowSurface(m_window);
	assert(m_surface != nullptr && "Renderer surface cannot be null");

	create_scene();  /* create the scene with triangles. */
}

void Renderer::Render()
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

			for(int i{ 0 }; i < NUM_TRIS; ++i)
			{
				IntersectTri(ray, tri[i]);  /* check if the ray intersects with the triangle. */
				if (ray.t < 1e30f)  /* if the ray intersects with the triangle, draw it. */
				{
					SDL_WriteSurfacePixel(m_surface, x, y, 0xFF, 0xFF, 0xFF, 0xFF);  /* draw the pixel with a random color. */
				}
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
