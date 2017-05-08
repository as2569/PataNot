#ifndef _GAMEFUNCTIONS_H_
#define _GAMEFUNCTIONS_H_
#define FRAME_SAMPLE_LENGTH 45

class GameFunctions
{
public: 
	void deltaTime();
	void loadSong(int choice);
	void cleanupSong();
	int playMusic();
	void avgNormVec();
	void musicFinished();
	void musicDone();
	float delta;
	Mix_Music *music;

private:
	long last;
};

#endif