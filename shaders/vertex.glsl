#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float offset;

out vec2 TexCoord;
out vec4 vEyeSpacePos;

void main()
{
	vec4 worldPosition = model * vec4(position, 1.0f);
	vec4 positionRelativeToCam = view * worldPosition;

	vEyeSpacePos = positionRelativeToCam;

	gl_Position = projection * view * worldPosition;
	TexCoord = texCoord + vec2(0.0f, offset);
}
