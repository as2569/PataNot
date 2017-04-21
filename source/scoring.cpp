#include <glm/glm.hpp>  
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/string_cast.hpp>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SOIL.h>
#include <time.h>

#include "Leap.h"
#include "simple_logger.h"
#include "graphics3d.h"
#include "shader.h"
#include "sprite.h"
#include "entity.h"
#include "gameFunctions.h"
#include "scoring.h"

glm::mat4 Scoring::mat;
int Scoring::score;
Sprite* firstDigit;
Sprite* secondDigit;

void Scoring::checkEnt(Entity *e)
{
	mat = e->getMatrix();
	float f = mat[3][1];
	if((f < 0.01f && f > -0.01f) && e->inUse)
	{
		e->freeEntity(e);
		score++;
		displayScore();
		//std::cout << score << std::endl;
	}
}

void Scoring::checkEntities()
{
	for(int i = 0; i < Entity::entList.size(); i++)
	{
		checkEnt(Entity::getEnt(i));
	}
}

void Scoring::displayScore()
{
	int f = score / 10;
	int s = score - (f * 10);
	std::cout << f << "  " << s << std::endl;
}