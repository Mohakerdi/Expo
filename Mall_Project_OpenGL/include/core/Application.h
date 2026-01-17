#pragma once
#include "core.h"
#include "Window.h"
#include "Scene.h"

class Application {
public:
    Application();
    ~Application();

    void run();

    void onCursorPositionEvent(double x, double y);
    void processDiscreteInput(int32_t key, int32_t scancode, int32_t action, int32_t mode);

    Window& getWindow() { return window; }

    static Application& instance() { return *instancePtr; }

    static Application* instancePtr;
    static float deltaTime;
    GLFWwindow* getGLFWwindow() const { return window.getGLFWwindow(); }

private:
    Window window;
    Scene scene;              
    myImGuiManager myImGui;
    float lastFrame;

    void SetupBasics();
    void Clear();
    void UpdateDeltaTime();
};
