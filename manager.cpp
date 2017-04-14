#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <GL\glew.h>
#include <SDL.h>
#include <iostream>
#include "Sprite.h"
#include "Entity.h"
#include "gameFunctions.h"
#include "entity.h"
#include "manager.h"

//Manager::Manager()
//{
//	//std::vector<Entity> entList;
//	//entList.resize(10);
//	//std::vector<Entity>::iterator iterator = entList.begin();
//	//while(iterator != entList.end())
//	//{
//	//	(*iterator) = NULL;
//	//}
//}

//Manager::~Manager()
//{
//	entList.clear();
//}

void Manager::randomSpawn(float BPM, int firstBeat)
{
	timing = (1 / (BPM / 60)) * 1000;
	currentTime = SDL_GetTicks();
	if(currentTime >= lastBeat + timing )
	{
		std::cout << currentTime << " beat" << std::endl;
		lastBeat = currentTime;
	}	
}

//void Manager::addEnt(Entity* e)
//{
//	entList.push_back(e);
//}
//
//void Manager::removeEnt(Entity* e)
//{
//	std::vector<Entity*>::iterator iterator = entList.begin();
//	while(iterator != entList.end())
//	{
//		if((*iterator) == e)
//		{
//			entList.erase(iterator);
//		}
//	}
//}