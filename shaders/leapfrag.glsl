#version 400
uniform vec3 leapVector;
out vec4 outputColor;


void main()
{
	
	outputColor = vec4(leapVector, 1);

}
