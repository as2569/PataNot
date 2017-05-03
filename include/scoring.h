#ifndef _SCORING_H_
#define _SCORING_H_

class Scoring
{
public:
	static glm::mat4 mat;
	static glm::mat4 firstDigitPos;
	static glm::mat4 secondDigitPos;
	static glm::mat4 firstHighPos;
	static glm::mat4 secondHighPos;
	static Entity* ent;
	static Sprite* firstDigit;
	static Sprite* secondDigit;
	static Sprite* firstDigitScore;
	static Sprite* secondDigitScore;
	static int highScore;
	static int score;
	static Leap::Vector leapVec;

	static void readScore();
	static void writeScore();
	static void checkEnt(Entity *e);
	static void checkEntities();
	static void setupScore();
	static void setupHighScore();
	static void displayScore();
	static void displayHighScore();
	static int gesture(Entity *e);
	
};

#endif