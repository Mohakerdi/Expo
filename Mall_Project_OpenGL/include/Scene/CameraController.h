#pragma once

#include "Camera.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

class CameraController
{
public:
    explicit CameraController(Camera& cam) : camera(cam) {}

    void processKeyboard(GLFWwindow* window, float dt)
    {
        glm::vec3 forward = glm::normalize(glm::vec3(cos(glm::radians(camera.yaw)), 0.0f, sin(glm::radians(camera.yaw))));
        glm::vec3 up = { 0.0f, 1.0f, 0.0f };
        glm::vec3 right = glm::normalize(glm::cross(forward, up));
        float v = moveSpeed * dt;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.position += forward * v;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.position -= forward * v;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.position -= right * v;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.position += right * v;
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) camera.position += up * v;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) camera.position -= up * v; 
    }

    void processMouse(double xpos, double ypos)
    {
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float dx = xpos - lastX;
        float dy = lastY - ypos; 
        lastX = xpos;
        lastY = ypos;

        camera.yaw += dx * mouseSensitivity;
        camera.pitch += dy * mouseSensitivity;

        camera.pitch = glm::clamp(camera.pitch, -89.0f, 89.0f);
    }

private:
    Camera& camera; 

    float moveSpeed = 15.0f;
    float mouseSensitivity = 0.2f;

    bool firstMouse = true;
    double lastX = 0.0, lastY = 0.0;
};
