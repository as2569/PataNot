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

int Sprite::getTiming(int step)
{
	return spriteFrames[step].timing;
}

void Sprite::setup()
{
	size.x = 0.25f;
	size.y = 1.0f;
	//spriteFrames[0].index = 0;
	//spriteFrames[1].index = 1;
	//spriteFrames[2].index = 2;
	//spriteFrames[3].index = 3;
	//spriteFrames[0].timing = 500;
	//spriteFrames[1].timing = 500;
	//spriteFrames[2].timing = 500;
	//spriteFrames[3].timing = 500;
	
	for(int i = 0; i > sizeof(spriteFrames) + 1; i++)
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

	GLuint model = glGetUniformLocation(graphics3d_get_shader_program(), "model");
	glUniformMatrix4fv(model, 1, GL_FALSE, &modelMatrix[0][0]);

	glBindTexture(GL_TEXTURE_2D, tex);

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
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}