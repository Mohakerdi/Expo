#include "Expo/Car/DrivableCar.h"
#include "Scene.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <cmath>
#include <algorithm>

DrivableCar::DrivableCar()
// --- SIZES (BIG SPORTS CAR) ---
    : m_ChassisMain(4.0f, 1.0f, 7.5f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_ChassisBottom(4.1f, 0.4f, 6.8f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_Hood(3.8f, 0.2f, 2.5f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_Trunk(3.8f, 0.2f, 1.5f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_SpoilerWing(3.6f, 0.1f, 1.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_SpoilerStrutL(0.2f, 0.5f, 0.2f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_SpoilerStrutR(0.2f, 0.5f, 0.2f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),

    // --- INTERIOR ---
    m_Dashboard(3.2f, 1.0f, 0.4f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_SteerRim(0.6f, 0.6f, 0.08f, 20, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_SteerSpokeH(1.2f, 0.08f, 0.08f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_SteerSpokeV(0.08f, 1.2f, 0.08f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_SteerHub(0.2f, 0.2f, 0.2f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),

    // --- GLASS ---
    m_WindshieldFront(3.6f, 1.2f, 0.2f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_WindshieldRear(3.6f, 1.0f, 0.2f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_WindowLeft(2.2f, 0.8f, 0.2f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_WindowRight(2.2f, 0.8f, 0.2f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag")
{
    this->setPosition(glm::vec3(0.0f, 0.8f, 0.0f));
    setTex();
}

void DrivableCar::setTex() {
    // 1. Car Body Paint
    std::string paint = "assets/textures/car_paint.jpg";
    m_ChassisMain.setAllFacesTexture(paint);
    m_Hood.setAllFacesTexture(paint);
    m_Trunk.setAllFacesTexture(paint);

    // 2. Underbody & Details
    m_ChassisBottom.setAllFacesTexture("assets/textures/plan/concrete.jpg");
    m_SpoilerWing.setAllFacesTexture(paint);
    m_SpoilerStrutL.setAllFacesTexture("assets/textures/plan/concrete.jpg");
    m_SpoilerStrutR.setAllFacesTexture("assets/textures/plan/concrete.jpg");

    // 3. Interior (Dark Grey Dashboard)
    m_Dashboard.setAllFacesTexture("assets/textures/plan/concrete.jpg");
    m_SteerRim.setSideTexture("assets/textures/plan/concrete.jpg");
    m_SteerRim.setTopTexture("assets/textures/plan/concrete.jpg");
    m_SteerRim.setBottomTexture("assets/textures/plan/concrete.jpg");
    m_SteerSpokeH.setAllFacesTexture("assets/textures/plan/concrete.jpg");
    m_SteerSpokeV.setAllFacesTexture("assets/textures/plan/concrete.jpg");
    m_SteerHub.setAllFacesTexture("assets/textures/plan/concrete.jpg");

    // 4. Glass (Transparent)
    // Ensure your glass.png has an alpha channel!
    m_WindshieldFront.setAllFacesTexture("assets/textures/glass.png", true);
    m_WindshieldRear.setAllFacesTexture("assets/textures/glass.png", true);
    m_WindowLeft.setAllFacesTexture("assets/textures/glass.png", true);
    m_WindowRight.setAllFacesTexture("assets/textures/glass.png", true);
}

void DrivableCar::UpdateCar(GLFWwindow* window, float dt) {
    // --- INTERACTION LOGIC ---
    static bool ePressed = false;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && !ePressed) {
        if (m_IsDriving) {
            // EXIT VEHICLE
            m_IsDriving = false;
            // Unlock cursor
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

            // Spawn camera to left side
            glm::vec3 carRight = glm::vec3(std::sin(glm::radians(m_RotationAngle + 90.0f)), 0, std::cos(glm::radians(m_RotationAngle + 90.0f)));
            glm::vec3 spawnPos = m_Position + (carRight * 5.0f) + glm::vec3(0, 1.0f, 0);

            Scene::setCameraPosition(spawnPos);

            // Reset head look
            m_HeadYaw = 0.0f;
            m_HeadPitch = 0.0f;

            // Look back at car
            glm::vec3 dirToCar = glm::normalize(m_Position - spawnPos);
            float lookAtYaw = glm::degrees(std::atan2(dirToCar.z, dirToCar.x));
            Scene::setCameraYaw(lookAtYaw);
            Scene::setCameraPitch(0.0f);

        }
        else {
            // TRY ENTER VEHICLE
            float dist = glm::length(Scene::getCameraPosition() - m_Position);
            if (dist < 10.0f) {
                m_IsDriving = true;
                // Lock cursor for driving
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                // Reset head look to center
                m_HeadYaw = 0.0f;
                m_HeadPitch = 0.0f;
            }
        }
        ePressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE) {
        ePressed = false;
    }

    // --- PHYSICS & INPUT ---
    if (m_IsDriving) {
        // Acceleration
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) m_Speed += 40.0f * dt;
        else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) m_Speed -= 30.0f * dt;
        else m_Speed *= 0.96f;

        // Steering
        if (std::abs(m_Speed) > 0.1f) {
            if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
                m_RotationAngle += 80.0f * dt;
                m_SteerAngle = 40.0f;
            }
            else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                m_RotationAngle -= 80.0f * dt;
                m_SteerAngle = -40.0f;
            }
            else m_SteerAngle = 0.0f;
        }

        // Move Car
        float rad = glm::radians(m_RotationAngle);
        m_Position.x += std::sin(rad) * m_Speed * dt;
        m_Position.z += std::cos(rad) * m_Speed * dt;

        // --- MOUSE LOOK (FPS INTERIOR) ---
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        // Calculate offset from center of screen
        float centerX = width / 2.0;
        float centerY = height / 2.0;

        float dx = xpos - centerX;
        float dy = ypos - centerY;

        // Sensitivity
        float sensitivity = 0.1f;
        m_HeadYaw -= dx * sensitivity;
        m_HeadPitch -= dy * sensitivity;

        m_HeadPitch = max(-89.0f, min(89.0f, (float)m_HeadPitch));

        // Reset mouse to center for next frame
        glfwSetCursorPos(window, centerX, centerY);

        // --- CAMERA HIJACK (COCKPIT VIEW) ---
        // 1. Calculate Vectors
        glm::vec3 carRight = glm::vec3(std::sin(glm::radians(m_RotationAngle + 90.0f)), 0, std::cos(glm::radians(m_RotationAngle + 90.0f)));
        glm::vec3 carForward = glm::vec3(std::sin(rad), 0, std::cos(rad));

        // 2. Driver Seat Offset (Adjusted for Cockpit feel)
        // Car Center Y is 0.8. Eyes should be at roughly 1.3 -> +0.5 offset.
        // Z offset: Moved to +0.2 to sit closer to the windshield/dashboard.
        glm::vec3 seatOffset = (carRight * -1.5f) + (carForward * 0.2f) + glm::vec3(0, 0.5f, 0);

        // 3. Set Position
        Scene::setCameraPosition(m_Position + seatOffset);

        // 4. Set Rotation (Car Body + Head Look)
        float finalYaw = m_RotationAngle + 90.0f + m_HeadYaw;
        Scene::setCameraYaw(finalYaw);
        Scene::setCameraPitch(m_HeadPitch);

    }
    else {
        // Friction when parked
        m_Speed *= 0.95f;
        if (std::abs(m_Speed) > 0.01f) {
            float rad = glm::radians(m_RotationAngle);
            m_Position.x += std::sin(rad) * m_Speed * dt;
            m_Position.z += std::cos(rad) * m_Speed * dt;
        }
        m_SteerAngle = 0.0f;
    }

    // Update Transform
    setRotation(m_RotationAngle, glm::vec3(0, 1, 0));
    updateModelMatrix();
}

void DrivableCar::drawOpaque() {
    glm::mat4 root = getModel();

    // --- 1. CHASSIS ---
    m_ChassisBottom.setParentModel(root);
    m_ChassisBottom.setPosition({ 0, 0.4f, 0 });
    m_ChassisBottom.drawOpaque();

    m_ChassisMain.setParentModel(root);
    m_ChassisMain.setPosition({ 0, 0.8f, -0.5f });
    m_ChassisMain.drawOpaque();

    m_Hood.setParentModel(root);
    m_Hood.setPosition({ 0, 1.2f, 2.5f });
    m_Hood.drawOpaque();

    m_Trunk.setParentModel(root);
    m_Trunk.setPosition({ 0, 1.2f, -3.2f });
    m_Trunk.drawOpaque();

    // --- 2. INTERIOR ---
    // MOVED DASHBOARD DOWN from 1.1f to 0.5f so it matches eye level
    m_Dashboard.setParentModel(root);
    m_Dashboard.setPosition({ 0, 0.5f, 1.5f });
    m_Dashboard.drawOpaque();

    // --- 3. STEERING WHEEL ---
    glm::mat4 wheelModel = glm::translate(root, glm::vec3(0.0f, 0.6f, 1.8f)); // Lowered steering wheel Y to 0.6
    wheelModel = glm::rotate(wheelModel, glm::radians(m_SteerAngle), glm::vec3(0.0f, 0.0f, 1.0f));
    wheelModel = glm::rotate(wheelModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    m_SteerRim.setParentModel(wheelModel);
    m_SteerRim.drawOpaque();
    m_SteerSpokeH.setParentModel(wheelModel);
    m_SteerSpokeH.drawOpaque();
    m_SteerSpokeV.setParentModel(wheelModel);
    m_SteerSpokeV.drawOpaque();
    m_SteerHub.setParentModel(wheelModel);
    m_SteerHub.drawOpaque();

    // --- 4. SPOILER ---
    m_SpoilerWing.setParentModel(root);
    m_SpoilerWing.setPosition({ 0, 1.6f, -3.0f });
    m_SpoilerWing.setRotation(10.0f, { 1,0,0 });
    m_SpoilerWing.drawOpaque();

    // --- 5. WHEELS ---
    m_WheelFL.setParentModel(root);
    m_WheelFL.setPosition({ -1.9f, 1.2f, 2.5f });
    m_WheelFL.setRotation(m_SteerAngle, { 0, 1, 0 });
    m_WheelFL.drawOpaque();

    m_WheelFR.setParentModel(root);
    m_WheelFR.setPosition({ 1.9f, 1.2f, 2.5f });
    m_WheelFR.setRotation(m_SteerAngle, { 0, 1, 0 });
    m_WheelFR.drawOpaque();

    m_WheelBL.setParentModel(root);
    m_WheelBL.setPosition({ -1.9f, 1.2f, -2.5f });
    m_WheelBL.drawOpaque();

    m_WheelBR.setParentModel(root);
    m_WheelBR.setPosition({ 1.9f, 1.2f, -2.5f });
    m_WheelBR.drawOpaque();
}

void DrivableCar::getTransparent() {
    glm::mat4 root = getModel();

    // --- 6. GLASS ---
    m_WindshieldFront.setParentModel(root);
    m_WindshieldFront.setPosition({ 0, 1.3f, 1.3f });
    m_WindshieldFront.setRotation(-30.0f, { 1, 0, 0 });
    Scene::addTransparent(&m_WindshieldFront);

    m_WindshieldRear.setParentModel(root);
    m_WindshieldRear.setPosition({ 0, 1.3f, -2.0f });
    m_WindshieldRear.setRotation(25.0f, { 1, 0, 0 });
    Scene::addTransparent(&m_WindshieldRear);

    m_WindowLeft.setParentModel(root);
    m_WindowLeft.setPosition({ -2.0f, 1.4f, -0.2f });
    m_WindowLeft.setRotation(5.0f, { 0, 1, 0 });
    Scene::addTransparent(&m_WindowLeft);

    m_WindowRight.setParentModel(root);
    m_WindowRight.setPosition({ 2.0f, 1.4f, -0.2f });
    m_WindowRight.setRotation(-5.0f, { 0, 1, 0 });
    Scene::addTransparent(&m_WindowRight);
}

void DrivableCar::onImguiRender() {
    // ImGui::SliderFloat("Speed", &m_Speed, -50.0f, 50.0f);
}