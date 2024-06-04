
#type vertex
#version 330

layout (location = 0) in vec4 a_Position;

uniform mat4 u_VPMatrix;
uniform mat4 u_MMatrix;

out vec4 v_Color;

void main()
{
	gl_Position = u_VPMatrix * u_MMatrix * a_Position;
}

#type fragment
#version 330

layout (location = 0) out vec4 f_Color;

void main()
{
    // gl_FragDepth = gl_FragCoord.z;
	// f_Color = vec4(gl_FragDepth, gl_FragDepth, gl_FragDepth, 1.f);
}