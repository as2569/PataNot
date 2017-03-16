#include <glm\glm.hpp>
#include <GL\glew.h>
#include "Sprite.h"

extern GLuint vbo;

void Sprite::draw(){

	float sprite[] = {
			0.0f, 0.0f, 0.0f, 1.0f,
			0.25f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f, 

			0.25f, 0.0f, 0.0f, 1.0f,
			0.25f, 1.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sprite), sprite, GL_STATIC_DRAW);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}