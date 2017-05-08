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
	int pos; //1 for left, 0 for right
	int symbol; //0 for up, 1 for right, 2 for left

	glm::mat4 getMatrix(); 
	int getStep();
	void update();
	void moveUp();
	void setup();
	void animate();
	void setSprite();
	void spawnPos();
	void draw();
	static void randomSpawn(float);
	static void drawEntities();
	static void updateEntities();
	static void reserve();
	static void freeEntity(Entity *e);
	static Entity *getEnt(int);
	static Entity *NewEntity();	
	Entity();

private:
	glm::vec3 posVec;

protected:
	
};

#endif 