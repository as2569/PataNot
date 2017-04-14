#ifndef _SPRITE_H_
#define _SPRITE_H_

struct frameData{
	int index;
	int timing;
};

class Sprite{
public:
	frameData spriteFrames[4];
	GLuint textureId; 	
	glm::vec2 size; 
	int width, height;
	unsigned char* image;
	
	int getTiming(int step);
	void draw(glm::mat4, int step);
	void update();
	void setup();

private:
	int i;
};

#endif 