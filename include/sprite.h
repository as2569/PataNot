#ifndef _SPRITE_H_
#define _SPRITE_H_
#define NUM_ANIMATION_FRAMES 1

struct frameData{
	int index;
	int timing;
};

class Sprite{
public:
	frameData spriteFrames[20];
	glm::vec2 size; 
	int width;
	int height;
	unsigned char* image;
	unsigned char* barTexture;
	unsigned char* scoreTexture;
	unsigned char* scoreGradient;

	
	int getTiming(int step);
	void update();
	void setup();
	void draw(glm::mat4, int step);
	void setupBar();
	void barDraw(glm::mat4);
	void setupScore();
	void drawScore(glm::mat4, int step);

private:
	int i;
};

#endif 