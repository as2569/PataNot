#ifndef _ENTITY_H_
#define	_ENTITY_H_

class Entity 
{
public:
	Sprite* sprite;

	int timeRemaining; 
	int currentStep;
	glm::mat4 modelMatrix;
	glm::vec3 translateVector;

	void update();
	void moveUp();
	void setup();
	void animate();
	void setSprite();
};

#endif 