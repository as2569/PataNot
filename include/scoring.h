#ifndef _SCORING_H_
#define _SCORING_H_

class Scoring
{
public:
	static glm::mat4 mat;
	static Entity* ent;

	static void checkEnt(Entity *e);
	static void checkEntities();
};

#endif