#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <GL\glew.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <simple_logger.h>
#include <vector>
#include <SDL.h>
#include "Sprite.h"
#include "Entity.h"
#include "gameFunctions.h"

extern GameFunctions gamefunctions;
std::vector<Entity> Entity::entList;

void Entity::reserve()
{
	Entity::entList.resize(5);
}

Entity::Entity()
{
	inUse = 0;
}

Entity *Entity::NewEntity()
{
	for(int i = 0; i < entList.size(); i++)
		if(!entList[i].inUse)
			return &entList[i];
	return NULL;
}

void Entity::setup()
{
	setSprite();
	timeRemaining = 500;
	timeAlive = 4000;
	currentStep = 0;
	modelMatrix = glm::mat4(1.0f);
	spawnPos();
	sprite->setup();
}

void Entity::randomSpawn(float BPM, int firstBeat)
{
	timing = (1 / (BPM / 60)) * 1000;
	currentTime = SDL_GetTicks();
	if(currentTime >= lastBeat + timing )
	{
		std::cout << currentTime << " beat" << std::endl;
		lastBeat = currentTime;
	}	
}

glm::mat4 Entity::getMatrix()
{
	return modelMatrix;
}

void Entity::spawnPos()
{
	pos = rand() % 2;
	std::cout << pos << std::endl; //console position and rotation

	if(pos == 1)
	{
		posVec = glm::vec3(0.5f, 0.0f, 0.0f);
		modelMatrix = glm::translate(modelMatrix, posVec);
	}

	if(pos == 0)
	{
		posVec = glm::vec3(-0.8f, 0.0f, 0.0f);
		modelMatrix = glm::translate(modelMatrix, posVec);
	}
}

int Entity::getStep()
{
	return currentStep;
}

void Entity::setSprite()
{
	sprite = new Sprite();
}

void Entity::moveUp()
{
	translateVector = glm::vec3(0.0f, 0.005f, 0.0f);
	modelMatrix = glm::translate(modelMatrix, translateVector);
}

void Entity::update()
{
	moveUp();
	animate();
	sprite->draw(modelMatrix, getStep());
	timeAlive -= gamefunctions.delta;
	//::cout << timeAlive<< std::endl;
	if(timeAlive <= 0)
	{
		;
	}
}

void Entity::animate()
{
	timeRemaining -= gamefunctions.delta;
	if(timeRemaining <= 0)
	{		
		currentStep += 1;
		if(currentStep == 4)
		{
			currentStep = 0;
		}
		timeRemaining = sprite->getTiming(currentStep);
	}
} 


