#version 410 core

in vec2 TexCoord;

in vec4 vEyeSpacePos;

uniform sampler2D ourTexture;

out vec4 color;

const vec4 vFogColor = vec4(0.85, 0.85, 0.85, 0.0);
const float fStart = 0.0;
const float fEnd = 100.0;
const float fDensity = 0.03;

void main()
{
	float fFogCoord = abs(vEyeSpacePos.z /  vEyeSpacePos.w);
	float fogFactor = exp(-pow(fDensity*fFogCoord, 2.0));
	fogFactor = 1.0 - clamp(fogFactor, 0.0, 1.0);

	color = texture(ourTexture, TexCoord);

	
	color = mix(color, vFogColor, fogFactor);
} 
