#ifndef _MANAGER_H_
#define	_MANAGER_H_

class Manager
{
public: 
	//Manager(); //Constructor
	//~Manager(); //Destructor
	//void addEnt(Entity*);
	//void removeEnt(Entity*);
	void randomSpawn(float, int);

private:	
	float BPM;
	float lastBeat;
	float thisBeat;
	float timing;
	float currentTime;
};

#endif