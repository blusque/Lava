#type vertex
#version 330

layout (location = 0) in vec4 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;

uniform mat4 u_VPMatrix;
uniform mat4 u_MMatrix;
uniform mat4 u_NMatrix;
uniform mat4 u_LightspaceVPMatrix;

out vec3 v_Normal;
out vec3 v_Position;
out vec2 v_TexCoord;
out vec4 v_LightspacePosition;

void main()
{
    vec4 globalPosition = u_MMatrix * a_Position;
	gl_Position = u_VPMatrix * globalPosition;
	v_Normal = normalize(mat3(u_NMatrix) * a_Normal);
	v_Position = vec3(globalPosition);
	v_TexCoord = a_TexCoord;
	v_LightspacePosition = u_LightspaceVPMatrix * globalPosition;
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
in vec4 v_LightspacePosition;

uniform vec3 u_EyePosition;
uniform Material u_Material;

uniform ParallelLight u_ParallelLight;
uniform PointLight u_PointLight;
uniform SpotLight u_SpotLight;
uniform sampler2D u_ShadowMap;

float ShadowCalculation(vec4 lightspaceFragPos)
{
    vec3 projPos = lightspaceFragPos.xyz / lightspaceFragPos.w;
    
    projPos = projPos * 0.5f + 0.5f;
    
    float shadowDepth = 0.f;
    float currentDepth = projPos.z;
    
    if (currentDepth > 1.f)
        return 0.f;
    
    // PCF
    float shadow = 0.f;
    vec2 texelSize = 1.f / textureSize(u_ShadowMap, 0);
    float bias = 0.000001f;
    
    for (int x = -1; x < 2; x++)
    {
        for (int y = -1; y < 2; y++)
        {
            vec2 offset = vec2(float(x), float(y)) * texelSize;
            shadowDepth = texture(u_ShadowMap, projPos.xy + offset).r;
            shadow += currentDepth - bias > shadowDepth ? 1.f : 0.f;
        }
    }
    shadow /= 9.f;
    
    return shadow;
}

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
      
    float shadow = ShadowCalculation(v_LightspacePosition);
    
    return ambient + (1.f - shadow) * (diffuse + specular);
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

float near = 0.1f;
float far = 100.f;

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
	f_Color = vec4(parallelColor/* + pointColor + spotColor*/, 1.f);
	// float z = 2.f * near * far / (near + far - gl_FragCoord.z * (far - near));
	// z /= far;
	// f_Color = vec4(vec3(z), 1.f);
}