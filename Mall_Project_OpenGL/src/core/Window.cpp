#include "Window.h"
#include "Application.h"
#include <iostream>

int Window::s_Width = 1800;
int Window::s_Height = 900;

Window::Window(const std::string& title, int width, int height)
    : m_Title(title), windowedWidth(width), windowedHeight(height)
{
    if (!init())
    {
        std::cerr << "FATAL: Window initialization failed." << std::endl;
    }
}

Window::~Window()
{
    if (m_Window)
        glfwDestroyWindow(m_Window);
    glfwTerminate();
}

bool Window::init()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(windowedWidth, windowedHeight, m_Title.c_str(), nullptr, nullptr);
    if (!m_Window)
    {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_Window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return false;
    }

    setupCallbacks();
    glfwSwapInterval(1); 

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    return true; // Success!
}

void Window::setupCallbacks()
{
    glfwSetErrorCallback(onWindowError);
    glfwSetKeyCallback(m_Window, onKeyEvent);
    glfwSetCursorPosCallback(m_Window, onCursorPosition);
    glfwSetFramebufferSizeCallback(m_Window, onResized);

    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::swapBuffers() { glfwSwapBuffers(m_Window); }
bool Window::shouldClose() const { return glfwWindowShouldClose(m_Window); }
int Window::getWidth() { return s_Width; }
int Window::getHeight() { return s_Height; }
void Window::toggleFullscreen() { /* Later */ }

void Window::onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Application::instance().processDiscreteInput(key, scancode, action, mods);
}

void Window::onCursorPosition(GLFWwindow* window, double x, double y)
{
    Application::instance().onCursorPositionEvent(x, y);
}

void Window::onResized(GLFWwindow* window, int width, int height)
{
    s_Width = width;
    s_Height = height;
    glViewport(0, 0, width, height);
}

void Window::onWindowError(int errorCode, const char* description)
{
    std::cerr << "GLFW Error (" << errorCode << "): " << description << std::endl;
}
