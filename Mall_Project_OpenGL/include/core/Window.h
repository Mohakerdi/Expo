#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    Window(const std::string& title, int width, int height);
    ~Window();

    bool shouldClose() const;
    void swapBuffers();

    GLFWwindow* getGLFWwindow() const { return m_Window; }
    static int getWidth();
    static int getHeight();

private:
    bool init();

    void setupCallbacks();
    void toggleFullscreen();

    static void onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void onCursorPosition(GLFWwindow* window, double x, double y);
    static void onResized(GLFWwindow* window, int width, int height);
    static void onWindowError(int errorCode, const char* description);

    GLFWwindow* m_Window = nullptr;
    std::string m_Title;
    int windowedWidth;
    int windowedHeight;

    static int s_Width;
    static int s_Height;
};
