#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <iostream>
#include <GL\glew.h>
#include <SOIL.h>
#include <SDL.h>
#include "Sprite.h"

extern GLuint vbo;
extern GLuint tex;
extern GLuint uvs;
extern glm::mat4 matrixMVP;

int i;
float delta = 0.0;
long last;
long now = SDL_GetTicks();
glm::vec3 translateVector;


void Sprite::setup()
{
	modelMatrix = glm::mat4(1.0f);
}

void Sprite::deltaTime()
{
	if (SDL_GetTicks()> last)
	{
		delta = ((float)(SDL_GetTicks() - last));
		last = SDL_GetTicks();
	}
}

void Sprite::animate()
{
	timeRemaining -= delta;
	if(timeRemaining <= 0)
	{	
		timeRemaining = spriteFrames[currentStep].timing;
		currentStep += 1;
		if(currentStep == 4)
		{
			currentStep = 0;
		}		
	}
}

void Sprite::update()
{
	deltaTime();
	moveUp();
	animate();
}

void Sprite::moveUp()
{
	translateVector = glm::vec3(0.0f, 0.001f, 0.0f);
	//matrixMVP = matrixMVP * translateVector;
	matrixMVP = glm::translate(matrixMVP, translateVector); 
}

void Sprite::draw(){
	
	float sprite[] = 
	{
			0.0f, 0.0f, 0.0f, 1.0f,
			0.25f, 0.0f, 0.0f, 1.0f,
			0.0f, 0.25f, 0.0f, 1.0f, 

			0.25f, 0.0f, 0.0f, 1.0f,
			0.25f, 0.25f, 0.0f, 1.0f,
			0.0f, 0.25f, 0.0f, 1.0f,
	};

	float uvCoords[] =
	{
		(size.x * spriteFrames[currentStep].index), size.y,
		size.x * (spriteFrames[currentStep].index + 1), size.y, 
		(size.x * spriteFrames[currentStep].index), 0.0f,

		size.x * (spriteFrames[currentStep].index + 1), size.y,
		size.x * (spriteFrames[currentStep].index + 1), 0.0f, 
		(size.x * spriteFrames[currentStep].index), 0.0f,
	};

	int width, height;
	unsigned char* image = SOIL_load_image("frametest.png", &width, &height, 0, SOIL_LOAD_RGB);

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glGenerateMipmap(GL_TEXTURE_2D);
	
	SOIL_free_image_data(image);

	glEnableVertexAttribArray(0); 
	glBindBuffer(GL_ARRAY_BUFFER, vbo); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(sprite), sprite, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	
	glEnableVertexAttribArray(1); 
	glBindBuffer(GL_ARRAY_BUFFER, uvs); 
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvCoords), uvCoords, GL_STATIC_DRAW);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}