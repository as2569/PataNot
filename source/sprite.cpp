#include <glm\glm.hpp>
#include <GL\glew.h>
#include <SDL_image.h>
#include "Sprite.h"

extern GLuint vbo;
extern SDL_Renderer *renderer;

void Sprite::draw(){

	float sprite[] = 
	{
			0.0f, 0.0f, 0.0f, 1.0f,
			0.25f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f, 

			0.25f, 0.0f, 0.0f, 1.0f,
			0.25f, 1.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f,
	};

	

	glEnable(GL_TEXTURE_2D);
	SDL_Surface *image;
	image = IMG_Load("Texture.jpg");


	glBindBuffer(GL_ARRAY_BUFFER, vbo); 
	glEnableVertexAttribArray(0); 
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sprite), sprite, GL_STATIC_DRAW);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}