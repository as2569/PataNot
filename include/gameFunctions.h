#ifndef _GAMEFUNCTIONS_H_
#define _GAMEFUNCTIONS_H_

class GameFunctions
{
public: 
	void deltaTime();
	void loadSong();
	void cleanupSong();
	int playMusic();

	float delta;
	Mix_Music *music;

private:
	long last;
};

#endif