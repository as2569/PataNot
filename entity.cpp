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
#include "manager.h"


extern GameFunctions gamefunctions;
extern Manager manager;

void Entity::setup()
{
	setSprite();
	timeRemaining = 500;
	timeAlive = 4000;
	currentStep = 0;
	modelMatrix = glm::mat4(1.0f);
	spawnPos();
	sprite->setup();
	inUse = 1;
	manager.addEnt(this);
}

glm::mat4 Entity::getMatrix()
{
	return modelMatrix;
}

//void Entity::randomSpawn(int BPM)
//{
//	timing = BPM / 60;
//	currentTime = SDL_GetTicks() * 100;
//	if(timing + lastBeat > currentTime)
//	{
//		std::cout << "beat" << std::endl;
//		lastBeat = currentTime;
//	}	
//}

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


