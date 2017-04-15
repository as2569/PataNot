#ifndef _SCORING_H_
#define _SCORING_H_

class Scoring
{
public:
	static glm::mat4 mat;
	static glm::vec3 posVec;
	float f;

	static void checkEnt(Entity *e);
};

#endif