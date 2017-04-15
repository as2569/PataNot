#include <glm/glm.hpp>  
#include <iostream>
#include <fstream>
#include <cstring>
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
glm::vec3 Scoring::posVec;

void Scoring::checkEnt(Entity *e)
{
	mat = e->getMatrix();
	posVec = glm::vec3(mat[3][0], mat[3][1], mat[3][2]);
	//std::cout << to_string(posVec) << std::endl;
	float f = mat[3][1];
	if(f < 0.1f && f > -0.1f)
	{
		std::cout << "ping" << std::endl;
	}
}