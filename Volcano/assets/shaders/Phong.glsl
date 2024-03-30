#type vertex
#version 330

layout (location = 0) in vec4 a_Position;
layout (location = 1) in vec3 a_Normal;

uniform mat4 u_VPMatrix;
uniform mat4 u_PMatrix;
uniform mat4 u_VMatrix;
uniform mat4 u_MMatrix;
uniform mat4 u_NormalMatrix;

uniform vec3 u_LightPosition;

out vec3 v_Normal;
out vec3 v_Position;
out vec3 v_LightPosition;

void main()
{
    vec4 viewPosition = u_VMatrix * u_MMatrix * a_Position;
	gl_Position = u_PMatrix * viewPosition;
	v_Normal = mat3(u_VMatrix) * normalize(mat3(u_NormalMatrix) * vec3(u_MMatrix * vec4(a_Normal, 1.f)));
	v_Position = vec3(viewPosition);
	v_LightPosition = vec3(u_VMatrix * vec4(u_LightPosition, 1.f));
}

#type fragment
#version 330

layout (location = 0) out vec4 f_Color;

uniform vec4 u_Color;
uniform vec4 u_LightColor;

in vec3 v_Normal;
in vec3 v_Position;
in vec3 v_LightPosition;

void main()
{
    vec3 lightDir = normalize(v_LightPosition - v_Position);
    vec3 diffuse = vec3(max(dot(v_Normal, lightDir), 0.f) * u_LightColor);
    
    float ambientStrength = 0.4f;
    vec3 ambient = vec3(ambientStrength * u_LightColor);
    
    vec3 viewDir = normalize(-v_Position);
    vec3 reflectDir = reflect(-lightDir, v_Normal);
    float specularStrength = 0.5f;
    vec3 specular = specularStrength * vec3(
        pow(max(dot(viewDir, reflectDir), 0.f), 32) * u_LightColor);
    
	f_Color = vec4(u_Color.xyz * (diffuse + ambient + specular), u_Color.w * u_LightColor.w);
}