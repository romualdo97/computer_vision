#version 330 core

// vertex attributes
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;

// varying
out vec2 vUv;
out vec3 vPos;

void main()
{
	vUv = aUv;
	vPos = aPos;
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}