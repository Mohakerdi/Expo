// ==================== Application.cpp (الكود الجديد) ====================
#include "Application.h"
#include <spdlog/spdlog.h> // Assuming you have spdlog for logging
#include "../DebugTriangle.h" // include the header, not the .cpp

Application* Application::instancePtr = nullptr;
float Application::deltaTime = 0.0f;                            

Application::Application()  
    : lastFrame(0.0f),
    window("Expo", Window::getWidth(), Window::getHeight()),
    myImGui(Window::getWidth(), Window::getHeight())
    // The member 'scene' is automatically constructed here 
{
    spdlog::info("Starting Application");
    instancePtr = this;

    // The Window constructor has already run and initialized OpenGL successfully.
    // Now, we can safely initialize our scene which uses OpenGL functions.

    // DELETED: new Scene(); --> This created a memory leak.
    // DELETED: Scene::instancePtr->init(); --> This called init() on the wrong, leaked object.

    // CORRECT: Call init() on the actual member variable 'scene'.
    scene.init();
}

Application::~Application()
{
    instancePtr = nullptr;
}

void Application::run()
{
    SetupBasics();
    while (!window.shouldClose())
    {
        glfwPollEvents();
        UpdateDeltaTime();
        scene.processContinuousInput(deltaTime);
        Clear();

        // Draw your scene (skybox + world)
        scene.draw();

        // Temporary overlay check: draw debug triangle on top
        // Debug::DrawTestTriangle();

        window.swapBuffers();
    }
}

void Application::SetupBasics()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // temporary diagnostics:
    glDisable(GL_CULL_FACE); // disable culling while debugging
}

void Application::Clear()
{
    // temporary visible clear color to verify pipeline
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Application::UpdateDeltaTime()
{
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void Application::processDiscreteInput(int32_t key, int32_t scancode, int32_t action, int32_t mode)
{
    // Pass delta time for any potential physics-based calculations in input handling
    scene.processDiscreteInput(key, scancode, action, mode, deltaTime);
}

void Application::onCursorPositionEvent(double x, double y)
{
    scene.onCursorPositionEvent(x, y);
}
