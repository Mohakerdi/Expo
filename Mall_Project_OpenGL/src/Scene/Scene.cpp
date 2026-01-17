#include "Scene.h"
#include "Application.h"
#include "Window.h"
#include <algorithm>

Scene* Scene::instancePtr = nullptr;

Camera Scene::camera; 
CameraController Scene::cameraController(Scene::camera); 

glm::mat4 Scene::s_Proj = glm::perspective(
    glm::radians(45.0f),
    (float)Window::getWidth() / (float)Window::getHeight(),
    0.1f,
    1000.0f
);

std::vector<Object*> Scene::transparentObjects;

Scene::Scene()
{
    instancePtr = this;
    lastX = Window::getWidth() * 0.5f;
    lastY = Window::getHeight() * 0.5f;
}

Scene::~Scene()
{
    instancePtr = nullptr;
}

// In Scene.cpp

glm::mat4 Scene::getView()
{
    return camera.getView(); 
}

glm::mat4 Scene::getProjection()
{
    return s_Proj;
}

glm::vec3 Scene::getCameraPosition()
{
    return camera.position;
}

void Scene::updateProj()
{
    s_Proj = glm::perspective(
        glm::radians(45.0f),
        (float)Window::getWidth() / (float)Window::getHeight(),
        0.1f,
        1000.0f
    );
}

void Scene::draw()
{
    transparentObjects.clear();

    world.drawOpaque();
    world.getTransparent();

    drawTransparent();
}

void Scene::drawTransparent()
{
    glDepthMask(GL_FALSE);

    std::sort(transparentObjects.begin(), transparentObjects.end(),
        [](Object* a, Object* b)
        {
            return a->dist() > b->dist();
        });

    for (auto* obj : transparentObjects)
        obj->drawTransparent();

    glDepthMask(GL_TRUE);
}

void Scene::addTransparent(Object* obj)
{
    transparentObjects.push_back(obj);
}

void Scene::onCursorPositionEvent(double xpos, double ypos)
{
    cameraController.processMouse(xpos, ypos);
}

void Scene::processDiscreteInput(int32_t key, int32_t, int32_t action, int32_t, float)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(
            Application::instance().getWindow().getGLFWwindow(),
            true
        );
    }
}

void Scene::processContinuousInput(float deltaTime)
{
    GLFWwindow* window = Application::instance().getWindow().getGLFWwindow();
    cameraController.processKeyboard(window, deltaTime);
    cameraController.processKeyboard(window, deltaTime);
    world.update(window, deltaTime);
}

void Scene::setCameraPosition(const glm::vec3& pos) {
    camera.position = pos;
}

void Scene::setCameraYaw(float yaw) {
    camera.yaw = yaw;
}

void Scene::setCameraPitch(float pitch) {
    camera.pitch = pitch;
}

float Scene::getCameraYaw() {
    return camera.yaw;
}

float Scene::getCameraPitch() {
    return camera.pitch;
}
void Scene::onImguiRender()
{
}
void Scene::init()
{
    world.init();   // ⬅️ هنا الصح
}

