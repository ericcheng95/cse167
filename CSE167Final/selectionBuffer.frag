#version 330 core
// This is a sample fragment shader.

uniform int r;
uniform int g;
uniform int b;

// You can output many things. The first vec4 type output determines the color of the fragment
out vec4 color;

void main()
{
	color = vec4(r/255.0f, g/255.0f, b/255.0f, 0);
}
