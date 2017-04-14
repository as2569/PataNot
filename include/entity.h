#ifndef _ENTITY_H_
#define	_ENTITY_H_

class Entity 
{
public:
	static std::vector<Entity> entList;
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
	void randomSpawn(float, int);
	void addEnt(Entity);
	static Entity *NewEntity();
	static void reserve();
	Entity();

private:
	int pos; //0 for left, 1 for right
	glm::vec3 posVec;
	float BPM;
	float lastBeat;
	float thisBeat;
	float timing;
	float currentTime;

protected:
	
};

#endif 