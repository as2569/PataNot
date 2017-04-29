#version 400
in vec2 coord;
out vec4 outputColor;
uniform sampler2D sprite;
uniform sampler2D gradient;
uniform vec3 gradientRow;

void main()
{
	outputColor = vec4(
				texture(gradient, vec2(texture(sprite, coord).r, gradientRow.r)).rgb
				+ texture(gradient, vec2(texture(sprite, coord).g, gradientRow.g)).rgb
				+ texture(gradient, vec2(texture(sprite, coord).b, gradientRow.b)).rgb,
				texture(sprite, coord).a);

}