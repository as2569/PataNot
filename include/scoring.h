#ifndef _SCORING_H_
#define _SCORING_H_

class Scoring
{
public:
	static glm::mat4 mat;
	static Entity* ent;
	static Sprite* firstDigit;
	static Sprite* secondDigit;
	static int score;

	static void checkEnt(Entity *e);
	static void checkEntities();
	static void displayScore();
	
};

#endif