
#type vertex
#version 330

layout (location = 0) in vec4 a_Position;
layout (location = 1) in vec2 a_TexCoord;
layout (location = 2) in vec4 a_Color;

uniform mat4 u_VPMatrix;
uniform mat4 u_MMatrix;

out vec4 v_Color;

void main()
{
	gl_Position = u_VPMatrix * u_MMatrix * a_Position;
	v_Color = a_Color;
}

#type fragment
#version 330

in vec4 v_Color;

layout (location = 0) out vec4 f_Color;

void main()
{
	f_Color = v_Color;
}