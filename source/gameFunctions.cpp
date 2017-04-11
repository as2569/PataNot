#include <SDL.h>
#include "gameFunctions.h"


void GameFunctions::deltaTime()
{
	if (SDL_GetTicks()> last)
	{
		delta = ((float)(SDL_GetTicks() - last));
		last = SDL_GetTicks();
	}
};









