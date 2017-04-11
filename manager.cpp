#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <GL\glew.h>
#include "Sprite.h"
#include "Entity.h"
#include "gameFunctions.h"
#include "entity.h"
#include "manager.h"

Manager::Manager()
{
	std::vector<Entity*>::iterator iterator = entList.begin();
	while(iterator != entList.end())
	{
		(*iterator) = NULL;
	}
}

Manager::~Manager()
{
	entList.clear();
}

void Manager::addEnt(Entity* e)
{
	entList.push_back(e);
}

void Manager::removeEnt(Entity* e)
{
	std::vector<Entity*>::iterator iterator = entList.begin();
	while(iterator != entList.end())
	{
		if((*iterator) == e)
		{
			entList.erase(iterator);
		}
	}
}