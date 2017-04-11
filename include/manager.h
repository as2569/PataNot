#ifndef _MANAGER_H_
#define	_MANAGER_H_

class Manager
{
public: 
	Manager(); //Constructor
	~Manager(); //Destructor
	void addEnt(Entity*);
	void removeEnt(Entity*);

private:
	std::vector<Entity*> entList;

};

#endif