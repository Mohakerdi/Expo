#pragma once
#include "Object.h"
#include "Box.h"
#include "Cylinder.h"
#include <glm/glm.hpp>
#include <vector>

class Table : public Object {
public:
    Table();
    ~Table();

    void setPosition(const glm::vec3& pos);
    void setRotation(float angle, const glm::vec3& axis);
    void setScale(float s);

    void update(float dt);
    void drawOpaque();
    void drawTransparent();

private:
    void setTextures();
    glm::mat4 getModelMatrix();

    // Box للسطح
    Box m_TableTop;

    // Cylinders للأرجل
    Cylinder m_LegFL;
    Cylinder m_LegFR;
    Cylinder m_LegBL;
    Cylinder m_LegBR;

    // متغيرات التحول (Transformations) لتصحيح Error m_Scale
    glm::vec3 m_Position;
    float m_RotationAngle;
    glm::vec3 m_RotationAxis;
    float m_Scale;
};