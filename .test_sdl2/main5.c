#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define HEIGHT 640
#define WIDTH 480


int main(void)
{
	SDL_Window *window = NULL;
	SDL_Renderer *ren = NULL;
	SDL_Rect rect = {100, 100, 300, 300};
	int status = EXIT_FAILURE;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "ERROR SDL_Init: %s\n", SDL_GetError());
		goto Quit;
	}

	window = SDL_CreateWindow("draw line", SDL_WINDOWPOS_CENTERED,
											SDL_WINDOWPOS_CENTERED,
											HEIGHT, WIDTH, SDL_WINDOW_SHOWN);
	if (!window)
	{
		fprintf(stderr, "ERROR SDL_CreateWindow: %s\n", SDL_GetError());
		goto Quit;
	}

	ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!ren)
	{
		fprintf(stderr, "ERROR SDL_CreateWindow: %s\n", SDL_GetError());
		goto Quit;
	}

	/* dessine un ligne blanche e en diagonal */
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderDrawRect(ren, &rect);
	SDL_RenderPresent(ren);

	SDL_Delay(5000);
	status = EXIT_SUCCESS;
Quit:
	if (ren)
		SDL_DestroyRenderer(ren);
	if (window)
		SDL_DestroyWindow(window);
	SDL_Quit();
	return status;
}