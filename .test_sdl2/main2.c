#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define HEIGHT 900
#define WIDTH 600

int main(int argc, char **argv)
{
	/* creer une structure Window pour avoir un retour sur la fenetre */
	SDL_Window *window = NULL;
	/* creer une structure Renderer pour avoir un retour sur le rendu */
	SDL_Renderer *renderer = NULL;
	int status = EXIT_FAILURE;

	/* init ce qu'il faut pour utiliser tout ce qui graphic */
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
	{
		fprintf(stderr, "Error SDL_INIT_VIDEO: %s\n", SDL_GetError());
		goto Quit;
	}

	/* creer une fenetre avec : titre, position sur l'ecran x et y, hauteur
	et largeur de la fenetre et l'etat de la fenetre */
	window = SDL_CreateWindow("1st Window", SDL_WINDOWPOS_CENTERED,
											SDL_WINDOWPOS_CENTERED,
											HEIGHT, WIDTH, SDL_WINDOW_SHOWN);
	if (!window)
	{
		fprintf(stderr, "Error SDL_CreateWindow: %s\n", SDL_GetError());
		goto Quit;
	}
	/* creer un rendu avec la fenetre associe au rendu, le driver et le(s) flag(s) */
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		fprintf(stderr, "Error SDL_Renderer: %s\n", SDL_GetError());
		goto Quit;
	}
	/* attend un delay en ms */
	SDL_Delay(3000);

	status = EXIT_SUCCESS;

Quit:
	/* quitter SDL proprement sans fuite */
	if (renderer)
		SDL_DestroyRenderer(renderer); /* Detruit le rendu proprement */
	if (window)
		SDL_DestroyWindow(window); /* Detruit la fenetre proprement */
	SDL_Quit();
	return status;
}

/**
 * Il faut bien detruire le rendu avant la fenetre
**/