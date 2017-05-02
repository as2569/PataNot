#version 400
in vec2 Texcoord;
out vec4 outputColor;
uniform sampler2D tex;

void main()
{
	//Shader checkboard debug
	//float x = (gl_FragCoord.x - 512)/1024 * 2;
	//float y = (gl_FragCoord.y - 384)/768 * 2;

	//int col = int(step(-.5f, x) * step(x, 0)
	//+ 2 * step(0, x) * step(x, 0.5)
	//+ 3 * step(.5, x) * step(x, 1));

	//int row = int(step(0, y) * step(y, 0.5f)
	//+ 2 * step(-0.5f, y) * step(y, 0)
	//+ 3 * step(-1.0f, y) * step(y, -0.5f));

	//outputColor = modelMatrix[row][col] * theColor;
	//outputColor = vec4(gl_FragCoord.x/1024, gl_FragCoord.y/768, 0, 1);
	//outputColor = theColor;

	//Debug Shader
	//outputColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
		
	// Debug Texture UVs
	//outputColor = vec4(Texcoord, 0, 1); 

	outputColor = texture(tex, Texcoord);
}
