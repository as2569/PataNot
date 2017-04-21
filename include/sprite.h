#ifndef _SPRITE_H_
#define _SPRITE_H_

struct frameData{
	int index;
	int timing;
};

class Sprite{
public:
	frameData spriteFrames[4];
	glm::vec2 size; 
	int width, height;
	unsigned char* image;
	unsigned char* barTexture;
	
	int getTiming(int step);
	void update();
	void setup();
	void draw(glm::mat4, int step);
	void setupBar();
	void barDraw(glm::mat4);
	void setupScore();
	void drawScore();

private:
	int i;
};

#endif 