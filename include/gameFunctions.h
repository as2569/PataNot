#ifndef _GAMEFUNCTIONS_H_
#define _GAMEFUNCTIONS_H_
#define FRAME_SAMPLE_LENGTH 25

class GameFunctions
{
public: 
	void deltaTime();
	void loadSong();
	void cleanupSong();
	int playMusic();
	void avgNormVec();

	float delta;
	Mix_Music *music;

private:
	long last;
};

#endif