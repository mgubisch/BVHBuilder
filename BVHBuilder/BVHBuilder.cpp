// BVHBuilder.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Renderer.h"
#include "Timer.h"
#include "BVH.h"

/* We will use this renderer to draw into this window every frame. */
static SDL_Window* window = NULL;
static Renderer* renderer = nullptr;
static Scene scene;  /* Create a scene object to hold the triangles. */

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    SDL_SetAppMetadata("Example Renderer Clear", "1.0", "com.example.renderer-clear");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!(window = SDL_CreateWindow("BVHBuilder", 640, 640, 0))) {
        SDL_Log("Couldn't create window: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

	renderer = new Renderer();
	renderer->Init(window);  /* Initialize the renderer with the window surface. */

    {
		Timer timer;  /* Create a timer to measure the time taken to build the BVH. */
		timer.reset();  /* Reset the timer at the start of the program. */
		BuildBVH(scene);  /* Build the BVH for the scene. */
		auto elapsed = timer.elapsed();  /* Get the elapsed time for building the BVH. */
		SDL_Log("BVH build time: %.3f ms", elapsed * 1000.0f);  /* Log the BVH build time in milliseconds. */
    }

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void* appstate)
{
    const double now = ((double)SDL_GetTicks()) / 1000.0;  /* convert from milliseconds to seconds. */
   
	renderer->Clear();  /* clear the renderer surface. */
   
    renderer->Render(scene);	

	renderer->Present();  /* present the renderer surface to the window. */

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    /* SDL will clean up the window for us. */
}

