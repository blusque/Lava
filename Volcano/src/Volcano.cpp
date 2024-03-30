#include <Lava.h>
#include <LavaEntryPoint.h>

#include "EditorLayer.h"

namespace Lava
{
    class Volcano: public Application
    {
    public:
        ~Volcano() override = default;

    private:
        friend Application;
    
        Volcano() = default;
        Volcano(int alpha, std::string str) : m_Alpha(alpha), m_Str(std::move(str)) {}

        void OnBegin() override
        {
            LV_PROFILE_FUNCTION();
        
            Application::OnBegin();

            Push(new EditorLayer);

            LV_INFO("Alpha: {0}, Str: {1}", m_Alpha, m_Str);
        }

        int m_Alpha { 0 };
        std::string m_Str;
    };


    void RegisterApplication()
    {
        LV_PROFILE_FUNCTION();
    
        Application::Register<Volcano>(1, "Hello World!");
    }   
}
