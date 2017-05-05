#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <GL\glew.h>
#include <stdlib.h>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <time.h>
#include <simple_logger.h>
#include <vector>
#include <SDL.h>
#include <SDL_mixer.h>
#include <Leap.h>

#include "Sprite.h"
#include "Entity.h"
#include "gameFunctions.h"
#include "scoring.h"

extern GameFunctions gamefunctions;
std::vector<Entity> Entity::entList;
float Entity::lastBeat;
float Entity::thisBeat;
float Entity::timing;
float Entity::currentTime;

void Entity::reserve()
{
	Entity::entList.resize(5);
}

Entity::Entity()
{
	inUse = 0;
}

void Entity::updateEntities()
{
	for(int i = 0; i <entList.size(); i++)
	{
		if(entList[i].inUse)
		{
			entList[i].update();
		}
	}
}

void Entity::drawEntities()
{
	for(int i = 0; i <entList.size(); i++)
	{
		if(entList[i].inUse)
		{
			entList[i].draw();
		}
	}
}

Entity *Entity::getEnt(int i)
{
	return &entList[i];
}

Entity *Entity::NewEntity()
{
	for(int i = 0; i < entList.size(); i++)
	{
		if(!entList[i].inUse)
		{
			return &entList[i];
		}
	}
	return NULL;
}

void Entity::freeEntity(Entity *ent)
{
	ent->inUse = 0;
	ent->sprite = NULL;
}

void Entity::setup()
{
	inUse = 1;
	setSprite();
	timeRemaining = 500;
	timeAlive = 5000;
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
		Entity* ent = Entity::NewEntity();
		ent-> setup();
		//std::cout << currentTime << " beat" << std::endl;
		lastBeat = currentTime;
	}	
}

glm::mat4 Entity::getMatrix()
{
	return modelMatrix;
}

void Entity::spawnPos()
{
	symbol = rand() % 3;
	pos = rand() % 2;
	//std::cout << pos << symbol << std::endl; 

	if(pos == 0)
	{
		posVec = glm::vec3(0.55f, -0.8f, 0.0f);
		modelMatrix = glm::translate(modelMatrix, posVec);
	}

	if(pos == 1)
	{
		posVec = glm::vec3(-0.8f, -0.8f, 0.0f);
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
	timeAlive -= gamefunctions.delta;
	if(timeAlive <= 0)
	{
		Entity::freeEntity(this);
	}
}

void Entity::draw()
{
	sprite->draw(modelMatrix, getStep(), symbol);
}

void Entity::animate()
{
	timeRemaining -= gamefunctions.delta;
	if(timeRemaining <= 0)
	{		
		currentStep += 1;
		if(currentStep == NUM_ANIMATION_FRAMES)
		{
			currentStep = 0;
		}
		timeRemaining = sprite->getTiming(currentStep);
	}
} 


