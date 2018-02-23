#version 330 core

// vertex attributes
out vec4 fragColor;
/*
vec4 uintRGB(float r, float g, float b)
{
	return vec4(r/255.0, g/255.0, b/255.0, 1.0)
}*/

void main()
{
	// rgb(106, 176, 76)
	fragColor = vec4(106.0/255.0, 176.0/255.0, 76.0/255.0, 1.0);
}