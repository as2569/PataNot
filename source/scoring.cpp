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
glm::mat4 Scoring::firstDigitPos;
glm::mat4 Scoring::secondDigitPos;
Leap::Vector Scoring::leapVec;

Sprite* Scoring::firstDigit;
Sprite* Scoring::secondDigit;
int Scoring::score;
int f;
int s;

int Scoring::gesture(Entity *e)
{
	using namespace Leap;

	const Frame frame = controller.frame();
	HandList hands = frame.hands();
	int pos = e->pos;

	for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) //Not sure how iterator works
	{
		const Hand hand = *hl;
		//const Vector normal = hand.palmNormal();
		//const Vector direction = hand.direction();
		
		//Is hand left or right?
		std::string handType = hand.isLeft() ? "Left" : "Right";
		
		//Print states
		//std::cout << handType <<" "<< pos << std::endl;
		//std::cout << hand.direction() << std::endl;
    }
	return 1;
}

void Scoring::checkEnt(Entity *e)
{
	mat = e->getMatrix();
	float f = mat[3][1];
	if((f < 0.28f && f > 0.26f) && e->inUse)
	{
		gesture(e);
		//somecode to check if leap motion works
		e->freeEntity(e);
		score++;
		displayScore();
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
	firstDigit = new Sprite();
	secondDigit = new Sprite();

	firstDigitPos = glm::mat4(1.0f);
	secondDigitPos = glm::mat4(1.0f);

	firstDigitPos = glm::scale(firstDigitPos, glm::vec3(1.5f, 1.5f, 1.0f));
	secondDigitPos = glm::scale(secondDigitPos, glm::vec3(1.5f, 1.5f, 1.0f));

	firstDigitPos = glm::translate(firstDigitPos, glm::vec3(-0.1f, -0.1f, 0.0));
	secondDigitPos = glm::translate(secondDigitPos, glm::vec3(0.00f, -0.1f, 0.0));

	firstDigit-> setupScore();
	secondDigit-> setupScore();
}

void Scoring::displayScore()
{
	f = score / 10;
	s = score - (f * 10);

	firstDigit->drawScore(firstDigitPos, f);
	secondDigit->drawScore(secondDigitPos, s);	
	//std::cout << f << "  " << s << std::endl;
}