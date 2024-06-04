#include "lvpch.h"
#include "Material.h"

#include "Lava/Renderer/Renderer2D.h"
#include "Lava/Renderer/Shader.h"

#include <glm/gtc/type_ptr.hpp>

namespace Lava
{
    PhongMaterial::PhongMaterial()
    {
        m_Shader = Shader::Create();
        m_DiffuseTexture = Texture::Create(1, 1);
        m_SpecularTexture = Texture::Create(1, 1);
        auto const phongShaderContext = Shader::ParseShaderProgram(ASSETS_PATH(shaders/BlinnPhong.glsl));
        m_Shader->Compile(phongShaderContext);
    }

    PhongMaterial::PhongMaterial(const Ref<Texture>& diffuse, const Ref<Texture>& specular)
    {
        m_Shader = Shader::Create();
        m_DiffuseTexture = diffuse;
        m_SpecularTexture = specular;
        auto const phongShaderContext = Shader::ParseShaderProgram(ASSETS_PATH(shaders/BlinnPhong.glsl));
        m_Shader->Compile(phongShaderContext);
    }

    void PhongMaterial::SetParallelLight(const glm::vec3& lightDir, const glm::vec3& lightColor, float lightAmbient,
                                 float lightDiffuse) const
    {
        m_Shader->Bind();
        m_Shader->SetUniform3f("u_ParallelLight.direction", lightDir.x, lightDir.y, lightDir.z);
        m_Shader->SetUniform3f("u_ParallelLight.ambient",
            lightAmbient * lightColor.r, lightAmbient * lightColor.g, lightAmbient * lightColor.b);
        m_Shader->SetUniform3f("u_ParallelLight.diffuse",
            lightDiffuse * lightColor.r, lightDiffuse * lightColor.g, lightDiffuse * lightColor.b);
        m_Shader->SetUniform3f("u_ParallelLight.specular", lightColor.r, lightColor.g, lightColor.b);
    }

    void PhongMaterial::SetPointLight(const glm::vec3& lightPos, const glm::vec3& lightColor, float lightAmbient,
                                 float lightDiffuse) const
    {
        m_Shader->Bind();
        m_Shader->SetUniform3f("u_PointLight.position", lightPos.x, lightPos.y, lightPos.z);
        m_Shader->SetUniform3f("u_PointLight.ambient",
            lightAmbient * lightColor.r, lightAmbient * lightColor.g, lightAmbient * lightColor.b);
        m_Shader->SetUniform3f("u_PointLight.diffuse",
            lightDiffuse * lightColor.r, lightDiffuse * lightColor.g, lightDiffuse * lightColor.b);
        m_Shader->SetUniform3f("u_PointLight.specular", lightColor.r, lightColor.g, lightColor.b);
        m_Shader->SetUniform1f("u_PointLight.constant", 1.f);
        m_Shader->SetUniform1f("u_PointLight.linear", 0.09f);
        m_Shader->SetUniform1f("u_PointLight.quadratic", 0.f);
    }

    void PhongMaterial::SetSpotLight(const glm::vec3& lightPos, const glm::vec3& lightDir, const glm::vec3& lightColor, float lightAmbient,
                                 float lightDiffuse) const
    {
        m_Shader->Bind();
        m_Shader->SetUniform3f("u_SpotLight.position", lightPos.x, lightPos.y, lightPos.z);
        m_Shader->SetUniform3f("u_SpotLight.direction", lightDir.x, lightDir.y, lightDir.z);
        m_Shader->SetUniform1f("u_SpotLight.cutoff", glm::cos(glm::radians(12.5f)));
        m_Shader->SetUniform1f("u_SpotLight.outerCutoff", glm::cos(glm::radians(17.5f)));
        m_Shader->SetUniform3f("u_SpotLight.ambient",
            lightAmbient * lightColor.r, lightAmbient * lightColor.g, lightAmbient * lightColor.b);
        m_Shader->SetUniform3f("u_SpotLight.diffuse",
            lightDiffuse * lightColor.r, lightDiffuse * lightColor.g, lightDiffuse * lightColor.b);
        m_Shader->SetUniform3f("u_SpotLight.specular", lightColor.r, lightColor.g, lightColor.b);
    }

    void PhongMaterial::SetEyePosition(const glm::vec3& position) const
    {
        m_Shader->Bind();
        m_Shader->SetUniform3f("u_EyePosition", position.x, position.y, position.z);
    }

    void PhongMaterial::Bind() const
    {
        m_Shader->Bind();
        m_DiffuseTexture->Bind(0);
        m_SpecularTexture->Bind(1);
    }

    Ref<PhongMaterial> PhongMaterial::Instance(const glm::vec3& diffuse, const glm::vec3& specular,
                                               float strength)
    {
        auto instance = CreateRef<PhongMaterial>();
        
        // Branch 1
        auto const diffuseUVec3 = glm::uvec3(diffuse * 255.f);
        auto const specularUVec3 = glm::uvec3(specular * 255.f);
        auto diffuseRGB8 = glm::vec<4, uint8_t>(diffuseUVec3.r, diffuseUVec3.g, diffuseUVec3.b, 255);
        auto specularRGB8 = glm::vec<4, uint8_t>(specularUVec3.r, specularUVec3.g, specularUVec3.b, 255);
        instance->m_DiffuseTexture->SetData(value_ptr(diffuseRGB8), sizeof(uint32_t));
        instance->m_SpecularTexture->SetData(value_ptr(specularRGB8), sizeof(uint32_t));

        // Branch 2
        // auto const diffuseUVec3 = glm::uvec3(diffuse * 255.f);
        // auto const specularUVec3 = glm::uvec3(specular * 255.f);
        // auto diffuseRGB8 = diffuseUVec3.r << 24 | diffuseUVec3.g << 16 | diffuseUVec3.b << 8 | static_cast<uint32_t>(255);
        // auto specularRGB8 = specularUVec3.r << 24 | specularUVec3.g << 16 | specularUVec3.b << 8 | static_cast<uint32_t>(255);
        // LV_CORE_WARN("Diffuse Vec3: {0}, {1}, {2}", diffuseUVec3.r, diffuseUVec3.g, diffuseUVec3.b);
        // LV_CORE_WARN("Diffuse Color: {0}", diffuseRGB8);
        // instance->m_DiffuseTexture->SetData(&diffuseRGB8, sizeof(uint32_t));
        // instance->m_SpecularTexture->SetData(&specularRGB8, sizeof(uint32_t));
        
        instance->m_Shader->Bind();
        instance->m_Shader->SetUniform1i("u_Material.diffuse", 0);
        instance->m_Shader->SetUniform1i("u_Material.specular", 1);
        instance->m_Shader->SetUniform1f("u_Material.shininess", 32.f);
        instance->m_Shader->SetUniform1f("u_Material.specularStrength", strength);
        return instance;
    }

    Ref<PhongMaterial> PhongMaterial::Instance(const Ref<Texture>& diffuse, const Ref<Texture>& specular,
        float strength)
    {
        auto instance = CreateRef<PhongMaterial>(diffuse, specular);
        instance->m_Shader->Bind();
        instance->m_Shader->SetUniform1i("u_Material.diffuse", 0);
        instance->m_Shader->SetUniform1i("u_Material.specular", 1);
        instance->m_Shader->SetUniform1f("u_Material.shininess", 32.f);
        instance->m_Shader->SetUniform1f("u_Material.specularStrength", strength);
        return instance;
    }
}
