#include "Renderer.h"
#include <cassert>

void Renderer::Init(SDL_Window* window)
{
	assert(window != nullptr && "Renderer surface cannot be null");
	m_window = window;
	m_surface = SDL_GetWindowSurface(m_window);
	assert(m_surface != nullptr && "Renderer surface cannot be null");
}

void Renderer::Render()
{
	SDL_WriteSurfacePixel(m_surface, 320, 240, 0xFF, 0x00, 0x00, 0x00);  /* draw a red pixel at the center of the window. */
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
