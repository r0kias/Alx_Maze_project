#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define HEIGHT_SCREEN	600
#define WIDTH_SCREEN	800
#define HEIGHT_MAP		24
#define WIDTH_MAP		24

int main(void)
{
	/* 24 x 24; 1 = mur et 0 = vide */
	int map [HEIGHT_MAP][WIDTH_MAP] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	SDL_Window *window = NULL;
	SDL_Renderer *ren = NULL;
	SDL_Point player = {35, 33};
	SDL_Rect *rect = NULL;
	float h_rect = HEIGHT_SCREEN / HEIGHT_MAP, w_rect = WIDTH_SCREEN / WIDTH_MAP;
	SDL_Event event;
	int status = EXIT_FAILURE;
	int status_event = 1;
	int number_of_wall = 0, indx = 0;
	int i, j;
	int x_rect, y_rect = 0;

	/*compter le nombre de mure*/
	for (i = 0; i < HEIGHT_MAP; i++)
		for (j = 0; j < WIDTH_MAP; j++)
			if (map[i][j])
				number_of_wall++;

	/*creer le nombre de rectangle*/
	rect = malloc(sizeof(SDL_Rect) * number_of_wall);
	if (!rect)
	{
		fprintf(stderr, "Malloc error !\n");
		goto Quit;
	}

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
	{
		fprintf(stderr, "ERROR SDL_Init: %s\n", SDL_GetError());
		goto Quit;
	}

	window = SDL_CreateWindow("rectangle mouve", SDL_WINDOWPOS_CENTERED,
											SDL_WINDOWPOS_CENTERED,
											WIDTH_SCREEN, HEIGHT_SCREEN, SDL_WINDOW_SHOWN);
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

	/*creation de la map MAP*/

	for (i = 0; i < HEIGHT_MAP; i++)
	{
		x_rect = 0;
		for (j = 0; j < WIDTH_MAP; j++)
		{
			if (map[i][j])
			{
				rect[indx].x = x_rect;
				rect[indx].y = y_rect;
				rect[indx].w = w_rect;
				rect[indx].h = h_rect;
				indx++;
			}
			x_rect += w_rect;
		}
		y_rect += h_rect;
	}

	/*boucle d'affichage*/
	while (status_event)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				status_event = 0;
				break;	
			}
		}

		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_RenderClear(ren);
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderFillRects(ren, rect, number_of_wall);
		SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		SDL_RenderDrawPoint(ren, player.x, player.y);
		SDL_RenderPresent(ren);
	}

	status = EXIT_SUCCESS;
Quit:
	if (ren)
		SDL_DestroyRenderer(ren);
	if (window)
		SDL_DestroyWindow(window);
	if (rect)
		free(rect);
	SDL_Quit();
	
	return status;
}
