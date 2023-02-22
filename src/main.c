#include <stdio.h>
#include <stdbool.h>

#define SDL_MAIN_HANDLED
#include <SDL.h>


int main(int argc, char* args[])
{
	// Window
	SDL_Window* window = SDL_CreateWindow("RogueLike", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, NULL);
	if (!window)
	{
		SDL_Log("Could not create a window: %s", SDL_GetError());
		return -1;
	}

	// Renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
		return -1;
	}

	// Game Loop
	bool done = false;
	while (!done)
	{
		// Get the next event
		SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				done = true;
			}
		}

		// Set the color to cornflower blue and clear
		SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
		SDL_RenderClear(renderer);

		// Show the renderer contents
		SDL_RenderPresent(renderer);
	}

	// Cleanup
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
