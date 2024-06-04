
#type vertex
#version 330

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

void main()
{
	gl_Position = vec4(a_Position.xy, 0.f, 1.f);
	v_TexCoord = a_TexCoord;
}

#type fragment
#version 330

in vec2 v_TexCoord;

layout (location = 0) out vec4 f_Color;

uniform sampler2D u_Sampler;

void main()
{
	f_Color = texture(u_Sampler, v_TexCoord);
	// f_Color = vec4(v_TexCoord.xy, 0.f, 1.f);
}