#include "Expo/Flag.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Flag::Flag()
// Sign Board (اللوحة): عريضة ورفيعة
    : m_SignBoard(80.0f, 60.0f, 2.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),

    // Pole (العمود)
    m_Pole(3.0f, 3.0f, 200.0f, 16, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag")
{
    m_Position = { 0.0f, 0.0f, 0.0f };
    m_RotationAngle = 0.0f;
    m_RotationAxis = { 0.0f, 1.0f, 0.0f };
    m_Scale = 1.0f;
    setTextures();
}

Flag::~Flag() {}

void Flag::setPosition(const glm::vec3& pos) { m_Position = pos; }
void Flag::setRotation(float angle, const glm::vec3& axis) { m_RotationAngle = angle; m_RotationAxis = axis; }
void Flag::setScale(float s) { m_Scale = s; }

glm::mat4 Flag::getModelMatrix() {
    glm::mat4 model(1.0f);
    model = glm::translate(model, m_Position);
    model = glm::rotate(model, glm::radians(m_RotationAngle), m_RotationAxis);
    model = glm::scale(model, glm::vec3(m_Scale));
    return model;
}

void Flag::setTextures() {
    std::string metalTexture = "assets/textures/awesomeface.png";
    std::string signTexture = "assets/textures/advWelcome.png"; // يمكنك وضع صورة نص هنا

    m_Pole.setSideTexture(metalTexture);
    m_SignBoard.setAllFacesTexture(signTexture);
}

void Flag::update(float dt) { (void)dt; }

void Flag::drawOpaque() {
    updateModelMatrix();
    glm::mat4 root = getModelMatrix();

    m_SignBoard.setParentModel(root);
    m_Pole.setParentModel(root);

    // 1. العمود
    m_Pole.setPosition({ 0.0f, 100.0f, 0.0f }); // الارتفاع نصف 200
    m_Pole.drawOpaque();

    // 2. اللوحة
    m_SignBoard.setPosition({ 42.0f, 140.0f, 0.0f }); // يمين العمود، أعلى قليلاً
    m_SignBoard.drawOpaque();
}

void Flag::drawTransparent() { /* فارغ */ }
void Flag::getTransparent() { /* فارغ */ }

void Flag::onImguiRender() {
    ImGui::SliderFloat3("Flag Position", &m_Position.x, -100, 100);
}