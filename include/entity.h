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
	glm::vec3 currentPos;
	static float BPM;
	static float lastBeat;
	static float thisBeat;
	static float timing;
	static float currentTime;

	glm::mat4 getMatrix(); 
	int getStep();
	void update();
	void moveUp();
	void setup();
	void animate();
	void setSprite();
	void spawnPos();
	void draw();
	static void randomSpawn(float, int);
	static void drawEntities();
	static void updateEntities();
	static void reserve();
	static void freeEntity(Entity *e);
	static Entity *getEnt();
	static Entity *NewEntity();	
	Entity();

private:
	int pos; //0 for left, 1 for right
	glm::vec3 posVec;

protected:
	
};

#endif 