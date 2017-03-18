#ifndef _SPRITE_H_
#define _SPRITE_H_

struct frameData{
	int index;
	int timing;
};

class Sprite{
	public:
		frameData spriteFrames[4];
		int timeRemaining; 
		int currentStep;
		glm::vec2 size; 
		GLuint textureId; 
		int flags;

		void draw();
		void update();
		void timeLeft();
		void deltaTime();
};

#endif 