#pragma once

#include <SDL3/SDL.h>

class Renderer
{
public:
	Renderer() = default;
	~Renderer() = default;
	void Init(SDL_Window* window);
	void Render();
	void Clear();
	void Present();
	void Shutdown();

private:
	SDL_Window* m_window{ nullptr };
	SDL_Surface* m_surface{ nullptr };
};

