#ifndef _ENTITY_H_
#define	_ENTITY_H_

class Entity 
{
public:
	Sprite* sprite;

	int timeRemaining; 
	int currentStep;
	int inUse;
	int timeAlive;

	glm::vec3 translateVector;
	glm::mat4 modelMatrix;

	glm::mat4 getMatrix();
	 
	int getStep();
	void update();
	void moveUp();
	void setup();
	void animate();
	void setSprite();
	void spawnPos();
	void randomSpawn(int BPM);

private:
	int pos; //0 for left, 1 for right
	glm::vec3 posVec;

};

#endif 