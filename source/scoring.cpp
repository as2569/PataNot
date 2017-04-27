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

extern Leap::Controller controller;
extern Leap::Listener listener;

glm::mat4 Scoring::mat;
int Scoring::score;
int f, s;
Sprite* firstDigit;
Sprite* secondDigit;

int Scoring::gesture(Entity *e)
{
	using namespace Leap;

	const Frame frame = controller.frame();
	HandList hands = frame.hands();
	int pos = e->pos;

	for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl)\
	{
		const Hand hand = *hl;
		const Vector normal = hand.palmNormal();
		const Vector direction = hand.direction();
		
		//Is hand left or right?
		//std::string handType = hand.isLeft() ? "Left" : "Right";
		std::string handType = hand.isLeft() ? "0" : "1";

		//Print states
		std::cout << handType <<" "<< pos << std::endl;
    }
	return 1;
}

void Scoring::checkEnt(Entity *e)
{
	mat = e->getMatrix();
	float f = mat[3][1];
	if((f < 0.01f && f > -0.01f) && e->inUse)
	{
		gesture(e);
		//somecode to check if leap motion works
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

void Scoring::setupScore()
{
	//firstDigit-> drawScore();
	//secondDigit-> drawScore();
}

void Scoring::displayScore()
{
	f = score / 10;
	s = score - (f * 10);
	//std::cout << f << "  " << s << std::endl;
}