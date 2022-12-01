#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define HEIGHT 900
#define WIDTH 600

int main(int argc, char **argv)
{
	/* creer une structure Window pour avoir un retour sur la fenetre */
	SDL_Window *window = NULL;
	int status = EXIT_FAILURE;

	/* init ce qu'il faut pour utiliser tout ce qui graphic */
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
	{
		fprintf(stderr,"Error SDL_INIT_VIDEO: %s\n", SDL_GetError());
		goto Quit;
	}

	/* creer une fenetre avec : titre, position sur l'ecran x et y, hauteur
	et largeur de la fenetre et l'etat de la fenetre */
	window = SDL_CreateWindow("1st Window", SDL_WINDOWPOS_CENTERED,
											SDL_WINDOWPOS_CENTERED,
											HEIGHT, WIDTH, SDL_WINDOW_SHOWN);
	if (!window)
	{
		fprintf(stderr,"Error SDL_CreateWindow: %s\n", SDL_GetError());
		goto Quit;
	}
	/* attend un delay en ms */
	SDL_Delay(1000);

	/*Detruit la fenetre proprement*/
	SDL_DestroyWindow(window);
	status = EXIT_SUCCESS;

Quit:
	/* quitter SDL proprement sans fuite */
	SDL_Quit();
	return status;
}
