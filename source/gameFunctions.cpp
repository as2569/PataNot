#include <SDL_mixer.h>
#include <SDL.h>
#include <iostream>
#include <Leap.h>
#include "gameFunctions.h"

extern int bpm;

void GameFunctions::deltaTime()
{
	if (SDL_GetTicks()> last)
	{
		delta = ((float)(SDL_GetTicks() - last));
		last = SDL_GetTicks();
	}
};

void GameFunctions::loadSong(int choice)
{
	if(choice == 1)
	{ 
		bpm = 40;
		if((music = Mix_LoadMUS("barbie192.mp3")) == NULL)
		{
			std::cout<< Mix_GetError()<<std::endl;
		}
	}
	if(choice == 2)
	{
		bpm = 40;
		if((music = Mix_LoadMUS("NJIT.mp3")) == NULL)
		{
			std::cout<< Mix_GetError()<<std::endl;
		}
	}
	if(choice == 3)
	{
		bpm == 20;
		if((music = Mix_LoadMUS("NJIT192.mp3")) == NULL)
		{
			std::cout<< Mix_GetError()<<std::endl;
		}
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
		if( Mix_PlayMusic(music, 1 ) == -1 )
		{
			std::cout << "playing" << std::endl;	
		}    
		return 1;
     }
	 //else
	 //{
		// Mix_HaltMusic();
		// return 1;
	 //}
}








