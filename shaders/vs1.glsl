#version 400
in vec4 position;
in vec4 color;
out vec4 theColor;
uniform mat4 modelMatrix;

void main()
{
	gl_Position = modelMatrix * position;
	//gl_Position = position;
	theColor = color;
}
