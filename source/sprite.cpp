#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <iostream>
#include <GL\glew.h>
#include <SOIL.h>
#include <SDL.h>
#include <graphics3d.h>
#include <vector>
#include "Sprite.h"
#include "Entity.h"

extern GLuint vbo;
extern GLuint tex;
extern GLuint uvs;
extern GLuint barTex;
extern GLuint bar;
extern GLuint baruvs;
extern GLuint digitTex;
extern GLuint digit;
extern GLuint digituvs;

int Sprite::getTiming(int step)
{
	return spriteFrames[step].timing;
}

void Sprite::setup()
{
	size.x = 0.25f;
	size.y = 1.0f;

	for(int i = 0; i < 4; i++)
	{
		spriteFrames[i].index = i;
		spriteFrames[i].timing = 500;
	}

	image = SOIL_load_image("frametest.png", &width, &height, 0, SOIL_LOAD_RGB);

	//Set up buffer
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
}

void Sprite::draw(glm::mat4 modelMatrix, int step){

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
		(size.x * spriteFrames[step].index), size.y,
		size.x * (spriteFrames[step].index + 1), size.y, 
		(size.x * spriteFrames[step].index), 0.0f,

		size.x * (spriteFrames[step].index + 1), size.y,
		size.x * (spriteFrames[step].index + 1), 0.0f, 
		(size.x * spriteFrames[step].index), 0.0f,
	};

	GLuint model = glGetUniformLocation(graphics3d_get_shader_program(0), "model");
	glUniformMatrix4fv(model, 1, GL_FALSE, &modelMatrix[0][0]);

	glEnableVertexAttribArray(0); 
	glBindBuffer(GL_ARRAY_BUFFER, vbo); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(sprite), sprite, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	
	glEnableVertexAttribArray(1); 
	glBindBuffer(GL_ARRAY_BUFFER, uvs); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvCoords), uvCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindTexture(GL_TEXTURE_2D, tex); 
	glDrawArrays(GL_TRIANGLES, 0, 6); //Draw arrays
	glBindTexture(GL_TEXTURE_2D, 0); 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Sprite::setupBar()
{
	size.x = 1.0f;
	size.y = 1.0f;

	for(int i = 0; i < 4; i++)
	{
		spriteFrames[i].index = i;
		spriteFrames[i].timing = 1;
	}

	barTexture = SOIL_load_image("digits.png", &width, &height, 0, SOIL_LOAD_RGB);

	//Set up buffer
	glGenTextures(1, &barTex);
	glBindTexture(GL_TEXTURE_2D, barTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, barTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(barTexture);
}

void Sprite::barDraw(glm::mat4 modelMatrix){

	int step = 0;

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
		(size.x * spriteFrames[step].index), size.y,
		size.x * (spriteFrames[step].index + 1), size.y, 
		(size.x * spriteFrames[step].index), 0.0f,

		size.x * (spriteFrames[step].index + 1), size.y,
		size.x * (spriteFrames[step].index + 1), 0.0f, 
		(size.x * spriteFrames[step].index), 0.0f,
	};

	GLuint model = glGetUniformLocation(graphics3d_get_shader_program(0), "model");
	glUniformMatrix4fv(model, 1, GL_FALSE, &modelMatrix[0][0]);

	glEnableVertexAttribArray(0); 
	glBindBuffer(GL_ARRAY_BUFFER, bar); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(sprite), sprite, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	
	glEnableVertexAttribArray(1); 
	glBindBuffer(GL_ARRAY_BUFFER, baruvs); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvCoords), uvCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Sprite::setupScore()
{
	size.x = 0.1f;
	size.y = 1.0f;

	for(int i = 0; i < 10; i++)
	{
		spriteFrames[i].index = i;
		spriteFrames[i].timing = 1;
	}

	scoreTexture = SOIL_load_image("digits24.png", &width, &height, 0, SOIL_LOAD_RGBA);

	//Set up buffer
	glGenTextures(1, &digitTex);
	glBindTexture(GL_TEXTURE_2D, digitTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, scoreTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(scoreTexture);
}

void Sprite::drawScore(glm::mat4 modelMatrix, int step){

	float sprite[] = 
	{
			0.0f, 0.0f, 0.0f, 1.0f,
			0.1f, 0.0f, 0.0f, 1.0f,
			0.0f, 0.2f, 0.0f, 1.0f, 

			0.1f, 0.0f, 0.0f, 1.0f,
			0.1f, 0.2f, 0.0f, 1.0f,
			0.0f, 0.2f, 0.0f, 1.0f,
	};

	float uvCoords[] =
	{
		(size.x * spriteFrames[step].index), size.y,
		size.x * (spriteFrames[step].index + 1), size.y, 
		(size.x * spriteFrames[step].index), 0.0f,

		size.x * (spriteFrames[step].index + 1), size.y,
		size.x * (spriteFrames[step].index + 1), 0.0f, 
		(size.x * spriteFrames[step].index), 0.0f,
	};

	GLuint model = glGetUniformLocation(graphics3d_get_shader_program(0), "model");
	glUniformMatrix4fv(model, 1, GL_FALSE, &modelMatrix[0][0]);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnableVertexAttribArray(0); 
	glBindBuffer(GL_ARRAY_BUFFER, digit); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(sprite), sprite, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	
	glEnableVertexAttribArray(1); 
	glBindBuffer(GL_ARRAY_BUFFER, digituvs); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvCoords), uvCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);	

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, digitTex);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisable(GL_BLEND);
}