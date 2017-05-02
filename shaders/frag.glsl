#version 400
in vec2 Texcoord;
out vec4 outputColor;
uniform sampler2D sprite;
uniform sampler2D gradient;
uniform ivec3 gradientRow;

void main()
{
	vec3 g = (vec3(.5,.5,.5) + gradientRow) / 1024.0;

	outputColor = vec4(
				texture(gradient, vec2(texture(sprite, Texcoord).r, g.r)).rgb,
				//+ texture(gradient, vec2(texture(sprite, Texcoord).g +.5/1024, g.g)).rgb
				//+ texture(gradient, vec2(texture(sprite, Texcoord).b+.5/1024, g.b)).rgb,
				texture(sprite, Texcoord).a);
				//outputColor = vec4(texture(gradient, Texcoord).r, g.r,0,1);
	outputColor = texture(gradient,vec2(texture(sprite, Texcoord).r, g.r));
}
