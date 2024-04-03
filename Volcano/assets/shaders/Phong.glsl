#type vertex
#version 330

layout (location = 0) in vec4 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;

uniform mat4 u_VPMatrix;
uniform mat4 u_MMatrix;
uniform mat4 u_NMatrix;

out vec3 v_Normal;
out vec3 v_Position;
out vec2 v_TexCoord;

void main()
{
    vec4 globalPosition = u_MMatrix * a_Position;
	gl_Position = u_VPMatrix * globalPosition;
	v_Normal = normalize(/*mat3(u_NMatrix) * */mat3(u_MMatrix) * a_Normal);
	v_Position = vec3(globalPosition);
	v_TexCoord = a_TexCoord;
}

#type fragment
#version 330

layout (location = 0) out vec4 f_Color;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
    float specularStrength;
};

struct PointLight
{
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};

struct ParallelLight
{
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;
    float cutoff;
    float outerCutoff;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 v_Normal;
in vec3 v_Position;
in vec2 v_TexCoord;

uniform vec3 u_EyePosition;
uniform Material u_Material;

uniform ParallelLight u_ParallelLight;
uniform PointLight u_PointLight;
uniform SpotLight u_SpotLight;

vec3 ParallelLightRender(vec3 viewDir)
{
    vec3 lightDir = normalize(-u_ParallelLight.direction);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float diff = max(dot(v_Normal, lightDir), 0.f);
    float spec = pow(max(dot(v_Normal, halfwayDir), 0.f), u_Material.shininess);
    
    vec3 ambient = u_ParallelLight.ambient * vec3(texture(u_Material.diffuse, v_TexCoord));
    vec3 diffuse = diff * u_ParallelLight.diffuse * vec3(texture(u_Material.diffuse, v_TexCoord));
    vec3 specular = u_Material.specularStrength * spec * 
        u_ParallelLight.specular * vec3(texture(u_Material.specular, v_TexCoord));
       
    return ambient + diffuse + specular;
}

vec3 PointLightRender(vec3 viewDir)
{
    vec3 lightDir = normalize(u_PointLight.position - v_Position);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float diff = max(dot(v_Normal, lightDir), 0.f);
    float spec = pow(max(dot(v_Normal, halfwayDir), 0.f), u_Material.shininess);
    
    vec3 ambient = u_PointLight.ambient * vec3(texture(u_Material.diffuse, v_TexCoord));
    vec3 diffuse = diff * u_PointLight.diffuse * vec3(texture(u_Material.diffuse, v_TexCoord));
    vec3 specular = u_Material.specularStrength * spec * 
        u_PointLight.specular * vec3(texture(u_Material.specular, v_TexCoord));
        
    float dist = distance(v_Position, u_PointLight.position);
    float attenuation = 1.f / (u_PointLight.constant + u_PointLight.linear * dist + u_PointLight.quadratic * dist * dist);
        
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    return ambient + diffuse + specular;
}

vec3 SpotLightRender(vec3 viewDir)
{
    vec3 lightDir = normalize(u_SpotLight.position - v_Position);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float diff = max(dot(v_Normal, lightDir), 0.f);
    float spec = pow(max(dot(v_Normal, halfwayDir), 0.f), u_Material.shininess);
    
    vec3 ambient = u_SpotLight.ambient * vec3(texture(u_Material.diffuse, v_TexCoord));
    vec3 diffuse = diff * u_SpotLight.diffuse * vec3(texture(u_Material.diffuse, v_TexCoord));
    vec3 specular = u_Material.specularStrength * spec * 
        u_SpotLight.specular * vec3(texture(u_Material.specular, v_TexCoord));
        
    float theta = dot(lightDir, normalize(-u_SpotLight.direction));
    float epsilon = u_SpotLight.cutoff - u_SpotLight.outerCutoff;
    float intensity = clamp((theta - u_SpotLight.outerCutoff) / epsilon, 0.f, 1.f);
    
    ambient *= intensity;
    diffuse *= intensity;
    specular *= intensity;
    
    return ambient + diffuse + specular;
}

void main()
{
    vec3 viewDir = normalize(u_EyePosition - v_Position);
    
    // Parallel Light Sources
    vec3 parallelColor = ParallelLightRender(viewDir);
    
    // Point Light Sources
    vec3 pointColor = PointLightRender(viewDir);
    
    // Spot Light Sources
    vec3 spotColor = SpotLightRender(viewDir);
    
    // Combine
	f_Color = vec4(parallelColor + pointColor + spotColor, 1.f);
}