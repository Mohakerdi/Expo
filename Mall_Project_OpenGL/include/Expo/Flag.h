#pragma once
#include "Object.h"
#include "Box.h"
#include "Cylinder.h"
#include <glm/glm.hpp>
#include <vector>

class Flag : public Object {
public:
    Flag();
    ~Flag();

    void setPosition(const glm::vec3& pos);
    void setRotation(float angle, const glm::vec3& axis);
    void setScale(float s);

    void update(float dt);
    void drawOpaque();
    void drawTransparent();
    void getTransparent();
    void onImguiRender();

private:
    void setTextures();
    glm::mat4 getModelMatrix();

    Box m_SignBoard;     // اللوحة
    Cylinder m_Pole;      // العمود

    glm::vec3 m_Position;
    float m_RotationAngle;
    glm::vec3 m_RotationAxis;
    float m_Scale;
};