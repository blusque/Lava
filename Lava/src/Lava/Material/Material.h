#pragma once
#include <glm/vec3.hpp>

namespace Lava
{
    class Texture;
}

namespace Lava
{
    class Shader;

    class LAVA_API PhongMaterial
    {
    public:
        PhongMaterial();
        PhongMaterial(const Ref<Texture>& diffuse, const Ref<Texture>& specular);

        void SetParallelLight(const glm::vec3& lightDir, const glm::vec3& lightColor,
            float lightAmbient = 0.05f, float lightDiffuse = 0.3f) const;
        void SetPointLight(const glm::vec3& lightPos, const glm::vec3& lightColor,
            float lightAmbient = 0.05f, float lightDiffuse = 0.3f) const;
        void SetSpotLight(const glm::vec3& lightPos, const glm::vec3& lightDir, const glm::vec3& lightColor,
            float lightAmbient = 0.05f, float lightDiffuse = 0.3f) const;
        
        void SetEyePosition(const glm::vec3& position) const;
        void Bind() const;

        Ref<Shader> GetShader() const { return m_Shader; }
        
        static Ref<PhongMaterial> Instance(const glm::vec3& diffuse, const glm::vec3& specular, float strength);
        static Ref<PhongMaterial> Instance(const Ref<Texture>& diffuse, const Ref<Texture>& specular, float strength);
    private:
        Ref<Shader> m_Shader;
        struct Material
        {
            Ref<Texture> diffuse;
            glm::vec3 specular { 1.f };
            float shininess { 32.f };
            float specularStrength { 1.f };
        };
        Material m_Material;
        Ref<Texture> m_DiffuseTexture;
        Ref<Texture> m_SpecularTexture;
    };
}

