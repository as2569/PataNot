#version 400
in vec4 position;
in vec2 texcoord;
out vec2 Texcoord;
uniform mat4 VP;
uniform mat4 model;

void main()
{
	gl_Position = VP * model * position;
	Texcoord = texcoord;
}
