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
glm::mat4 Scoring::firstHighPos;
glm::mat4 Scoring::secondHighPos;
Leap::Vector Scoring::leapVec;

Sprite* Scoring::firstDigit;
Sprite* Scoring::secondDigit;
Sprite* Scoring::firstDigitScore;
Sprite* Scoring::secondDigitScore;

int Scoring::highScore;
int Scoring::score;
int f, s, hf, hs;

int Scoring::gesture(Entity *e)
{
	using namespace Leap;

	const Frame frame = controller.frame();
	HandList hands = frame.hands();
	int pos = e->pos;
	int sym = e->symbol;

	for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) //Not sure how iterator works
	{
		const Hand hand = *hl;
		HandList hands = controller.frame().hands();

		//Is hand left or right?
		std::string handType = hand.isLeft() ? "Left" : "Right";
		
		//Print states
		//std::cout << handType <<" "<< pos << std::endl;
		//std::cout << hand.direction().yaw() << std::endl;
		
		if(hand.isLeft() && (e->pos == 1 && e->symbol == 0))
		{
			if((hand.direction().yaw() > -0.4) && (hand.direction().yaw() < 0.4))
			{
				//if(hand.fingers().extended().count() == 2)
				//{
					std::cout << "left up " << hand.direction().yaw() <<std::endl;
					return 1;
				//}
			}
		}

		if(hand.isRight() && (e->pos == 0 && e->symbol == 0))
		{
			if((hand.direction().yaw() > -0.4) && (hand.direction().yaw() < 0.4))
			{
				//if(hand.fingers().extended().count() == 2)
				//{
					std::cout << "right up " << hand.direction().yaw() <<std::endl;
					return 1;
				//}
			}
		}

		if(hand.isLeft() && (e->pos == 1 && e->symbol == 1))
		{
			if((hand.direction().yaw() > 0.4) && (hand.direction().yaw() < 1.6))
			{
				//if(hand.fingers().extended().count() == 2)
				//{
					std::cout << "left right " << hand.direction().yaw() <<std::endl;
					return 1;
				//}
			}
		}

		if(hand.isRight() && (e->pos == 0 && e->symbol == 1))
		{
			if((hand.direction().yaw() > 0.4) && (hand.direction().yaw() < 1.6))
			{
				//if(hand.fingers().extended().count() == 2)
				//{
					std::cout << "right right " << hand.direction().yaw() <<std::endl;
					return 1;
				//}
			}
		}

		if(hand.isLeft() && (e->pos == 1 && e->symbol == 2))
		{
			if((hand.direction().yaw() < -0.4) && (hand.direction().yaw() > -1.6))
			{
				//if(hand.fingers().extended().count() == 2)
				//{
					std::cout << "left left " << hand.direction().yaw() <<std::endl;
					return 1;
				//}
			}
		}

		if(hand.isRight() && (e->pos == 0 && e->symbol == 2))
		{
			if((hand.direction().yaw() < -0.4) && (hand.direction().yaw() > -1.6))
			{
				//if(hand.fingers().extended().count() == 2)
				//{
					std::cout << "right right " << hand.direction().yaw() <<std::endl;
					return 1;
				//}
			}
		}
    }
	return 0;
}

void Scoring::checkEnt(Entity *e)
{
	mat = e->getMatrix();
	float f = mat[3][1];
	if((f < 0.28f && f > 0.26f) && e->inUse)
	//if((f < 0.12f && f > 0.10f) && e->inUse)
	{
		if(gesture(e))
		{
			//somecode to check if leap motion works
			e->freeEntity(e);
			score++;
			displayScore();
		}
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

void Scoring::setupHighScore()
{
	firstDigitScore = new Sprite();
	secondDigitScore = new Sprite();

	firstHighPos = glm::mat4(1.0f);
	secondHighPos = glm::mat4(1.0f);
	firstHighPos = glm::scale(firstHighPos, glm::vec3(0.7f, 0.7f, 1.0f));
	secondHighPos = glm::scale(secondHighPos, glm::vec3(0.7f, 0.7f, 1.0f));
	firstHighPos = glm::translate(firstHighPos, glm::vec3(-0.1f, -0.4f, 0.0));
	secondHighPos = glm::translate(secondHighPos, glm::vec3(0.00f, -0.4f, 0.0));

	firstDigitScore-> setupScore();
	secondDigitScore-> setupScore();
}

void Scoring::displayScore()
{
	f = score / 10;
	s = score - (f * 10);

	firstDigit->drawScore(firstDigitPos, f);
	secondDigit->drawScore(secondDigitPos, s);	
}

void Scoring::displayHighScore()
{
	hf = highScore / 10;
	hs = highScore - (hf * 10);

	firstDigitScore->drawScore(firstHighPos, hf);
	secondDigitScore->drawScore(secondHighPos, hs);
}

void Scoring::readScore()
{
	using namespace std;
	ifstream file;
	file.open("score.txt");
	if (!file)
	{
		cout << "File load fail" << endl;
		return;
	}
	file >> highScore;
	cout << highScore << endl;
	file.close();
}

void Scoring::writeScore()
{
	using namespace std;
	fstream file;
	file.open("score.txt", ios::out);
	highScore = score;
	file << highScore << endl;
	cout << "Written to file" << endl;
	file.close();

}

