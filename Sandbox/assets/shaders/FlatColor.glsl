
#type vertex
#version 330

layout (location = 0) in vec4 a_Position;

uniform mat4 u_VPMatrix;
uniform mat4 u_MMatrix;

void main()
{
	gl_Position = u_VPMatrix * u_MMatrix * a_Position;
}

#type fragment
#version 330

uniform vec3 u_Color;

layout (location = 0) out vec4 f_Color;

void main()
{
	f_Color = vec4(u_Color, 1.0f);
}