#ifndef _SCORING_H_
#define _SCORING_H_

class Scoring
{
public:
	static glm::mat4 mat;
	static glm::mat4 firstDigitPos;
	static glm::mat4 secondDigitPos;
	static Entity* ent;
	static Sprite* firstDigit;
	static Sprite* secondDigit;
	static int score;
	static Leap::Vector leapVec;

	static void checkEnt(Entity *e);
	static void checkEntities();
	static void setupScore();
	static void displayScore();
	static int gesture(Entity *e);
	
};

#endif