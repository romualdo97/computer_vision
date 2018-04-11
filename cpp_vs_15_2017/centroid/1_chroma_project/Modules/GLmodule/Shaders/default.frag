#version 330 core

// input as varying
in vec2 vUv;
in vec3 vPos;

// output
out vec4 fragColor;

void main()
{
	// rgb(106, 176, 76)
	//fragColor = vec4(106.0/255.0, 176.0/255.0, 76.0/255.0, 1.0);
	fragColor = vec4(1.0, vUv.y, 0.0, 1.0);
}