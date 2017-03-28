#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <GL\glew.h>
#include <iostream>
#include "Sprite.h"
#include "Entity.h"
#include "gameFunctions.h"


extern glm::mat4 matrixMVP;
extern GameFunctions func;

void Entity::setup()
{
	timeRemaining = 500;
	currentStep = 0;
	//modelMatrix = glm::mat4(1.0f);
	sprite->setup();
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
	translateVector = glm::vec3(0.0f, 0.10f, 0.0f);
	//modelMatrix = glm::translate(modelMatrix, translateVector);
	matrixMVP = glm::translate(matrixMVP, translateVector);
}

void Entity::update()
{
	moveUp();
	animate();
	//matrixMVP = modelMatrix;
	sprite->draw(matrixMVP, getStep());
}

void Entity::animate()
{
	timeRemaining -= func.delta;
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

