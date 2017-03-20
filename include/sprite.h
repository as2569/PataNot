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
		int flags;
		glm::vec2 size; 
		glm::mat4 modelMatrix;
		GLuint textureId; 		

		void draw();
		void update();
		void animate();
		void moveUp();
		void deltaTime();
		void setup();
};

#endif 