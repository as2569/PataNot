#version 400
in vec4 position;
in vec2 texcoord;
out vec2 Texcoord;
uniform mat4 matrixMVP;

void main()
{
	gl_Position = matrixMVP * position;
	//gl_Position = position;
	Texcoord = texcoord;
	//theColor = color;
}
