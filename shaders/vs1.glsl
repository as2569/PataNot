#version 400
in vec4 position;
in vec2 texcoord;
//in vec4 color;
//out vec4 theColor;
out vec2 Texcoord;
uniform mat4 modelMatrix;

void main()
{
	//gl_Position = modelMatrix * position;
	gl_Position = position;
	Texcoord = texcoord;
	//theColor = color;
}
