
#type vertex
#version 330

layout (location = 0) in vec4 a_Position;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TexCoord;
layout (location = 3) in float a_TexIndex;

uniform mat4 u_VPMatrix;

out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexIndex;

void main()
{
    gl_Position = u_VPMatrix * a_Position;
    v_Color = a_Color;
    v_TexCoord = a_TexCoord;
    v_TexIndex = a_TexIndex;
}

#type fragment
#version 330

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;

uniform sampler2D u_TexSamplers[32];

layout (location = 0) out vec4 f_Color;

void main()
{
    f_Color = texture(u_TexSamplers[int(v_TexIndex)], v_TexCoord) * v_Color;
    // f_Color = v_Color;
}