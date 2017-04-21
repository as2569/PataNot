#include <SDL_mixer.h>
#include <SDL.h>
#include <iostream>
#include "gameFunctions.h"

void GameFunctions::deltaTime()
{
	if (SDL_GetTicks()> last)
	{
		delta = ((float)(SDL_GetTicks() - last));
		last = SDL_GetTicks();
	}
};

void GameFunctions::loadSong()
{
	if((music = Mix_LoadMUS("barbie.mp3")) == NULL)
	{
		std::cout<< Mix_GetError()<<std::endl;
	}
	else
	{
		//std::cout << "loaded song" << std::endl;
	}
}

void GameFunctions::cleanupSong()
{
	Mix_FreeMusic(music);
	Mix_CloseAudio();
	std::cout << "cleanup" << std::endl;
}

int GameFunctions::playMusic()
{
	 //If there is no music playing
     if( Mix_PlayingMusic() == 0 )
     {
		//Play the music
		if( Mix_PlayMusic(music, -1 ) == -1 )
		{
			std::cout << "playing" << std::endl;
			return 1;
		}    
     }
}








