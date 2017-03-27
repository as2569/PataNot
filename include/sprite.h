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
	glm::mat4 modelMatrix;
	GLuint textureId; 	
	
	int getTiming(int step);
	void draw(glm::mat4, int step);
	void update();
	void animate();
	void setup();

private:
	int i;
	int step;
};

#endif 