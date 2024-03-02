
#type vertex
#version 330

layout (location = 0) in vec4 a_Position;
layout (location = 1) in vec2 a_TexCoord;

uniform mat4 u_VPMatrix;
uniform mat4 u_MMatrix;

out vec2 v_TexCoord;

void main()
{
    gl_Position = u_VPMatrix * u_MMatrix * a_Position;
    v_TexCoord = a_TexCoord;
}

#type fragment
#version 330

in vec2 v_TexCoord;

uniform sampler2D u_TexSampler;

layout (location = 0) out vec4 f_Color;

void main()
{
    f_Color = texture(u_TexSampler, v_TexCoord);
}