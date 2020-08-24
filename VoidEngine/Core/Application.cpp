#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/Core/Allocator.hpp>
#include <VoidEngine/Core/Time.hpp>
#include <VoidEngine/Core/World.hpp>
#include <VoidEngine/ECS/Entities/FirstPersonCamera.hpp>
#include <VoidEngine/Rendering/Shader.hpp>

namespace VOID_NS {
    Application::Application() : Application(ApplicationInfo::GetDefault()) {}

    Application::Application(ApplicationInfo info) {
        g_FixedUpdateInterval = info.FixedUpdateInterval;
        g_World     = Allocator::Allocate<World>(info);
        g_Renderer  = Allocator::Allocate<Renderer>(info);

        ShaderLibrary::CreateDefaultShaders();
    }

    Application::~Application() {
        Allocator::Free(g_Renderer);
    }

    Application     *g_Application;
    CameraComponent *g_Camera;
    Renderer        *g_Renderer;
    Window          *g_Window;
    World           *g_World;
    f32              g_FixedUpdateInterval;
};

int main(int argc, char **argv) {
    Void::ApplicationInfo k_DefaultInfo = Void::ApplicationInfo::GetDefault();
    Void::g_Application = Void::CreateApplication(k_DefaultInfo);

#if VOID_ENABLE_DEBUG
    Logger::LogInfo(
        "Void Engine, v%d.%d.%d",
        VOID_VERSION_MAJOR,
        VOID_VERSION_MINOR,
        VOID_VERSION_PATCH
    );

    Logger::LogInfo("GLFW, v%s", glfwGetVersionString());
#endif

    /* This will create a CameraComponent, and assign g_Camera. */ 
    if(!Void::g_Camera) {
        Allocator::Allocate<FirstPersonCamera>();
    }

    VOID_ASSERT(Void::g_Camera != nullptr, "g_Camera is nullptr.");

    Void::g_Application->Start();
    Void::g_World->Start();

    while(Void::g_Renderer->IsRunning()) {
        Void::Time::HandleDeltaTime();

        Void::g_Application->Update();
        Void::g_World->Update();

        Void::g_Renderer->Begin();
        Void::g_Renderer->Render();
        Void::g_Renderer->End();
    }

    Allocator::Free(g_Application);
    return 0;
}