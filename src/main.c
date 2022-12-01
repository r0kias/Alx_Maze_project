#include "raycaster.h"

/**
* main - main function
* Return: 0 Success, -1 Error
*/
int main(void)
{
	t_sdl sdl;
	t_raycaster rc;

	if (init(&sdl, &rc) != 0)
		return (-1);
	raycaster(&sdl, &rc);
	if (sdl.renderer)
		SDL_DestroyRenderer(sdl.renderer);
	if (sdl.window)
		SDL_DestroyWindow(sdl.window);
	SDL_Quit();
	return (0);
}
