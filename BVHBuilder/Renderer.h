#pragma once

#include <SDL3/SDL.h>
#include <glm/glm.hpp>

#include "Scene.h"

class Renderer
{
public:
	Renderer() = default;
	~Renderer() = default;
	void Init(SDL_Window* window);
	void Render(Scene& scene);
	void Clear();
	void Present();
	void Shutdown();

private:
	SDL_Window* m_window{ nullptr };
	SDL_Surface* m_surface{ nullptr };

	glm::vec3 m_cameraPos{ 0.0f, 0.0f, -18.0f };  // Camera position in world space

	//virtual camera plane
#if USE_TESTFILE
	const glm::vec3 p0{-2.5f, 0.8f, -0.5f};
	const glm::vec3 p1{-0.5f, 0.8f, -0.5f};
	const glm::vec3 p2{ -2.5f, -1.2f, -0.5f };
#else
	const glm::vec3 p0{-1.0f, 1.0f, -15.0f};
	const glm::vec3 p1{1.0f, 1.0f, -15.0f};
	const glm::vec3 p2{ -1.0f, -1.0f, -15.0f };
#endif
};

