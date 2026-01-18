#pragma once
#include "Object.h"
#include "Box.h"
#include "Cylinder.h"
#include <glm/glm.hpp>
#include <vector>

class Chair : public Object {
public:
    Chair();
    ~Chair();

    void setPosition(const glm::vec3& pos);
    void setRotation(float angle, const glm::vec3& axis);
    void setScale(float s);

    void update(float dt);
    void drawOpaque();
    void drawTransparent();
    void getTransparent();
    void onImguiRender();

private:
    void setTex();
    glm::mat4 getModelMatrix();

    // الأجزاء (Boxes)
    Box m_Seat;
    Box m_Backrest;
    Box m_ArmrestL;
    Box m_ArmrestR;

    // الأرجل (Cylinders) - تم تعريفها منفصلة مثل Table تماماً
    Cylinder m_LegFL;
    Cylinder m_LegFR;
    Cylinder m_LegBL;
    Cylinder m_LegBR;

    // متغيرات التحول
    glm::vec3 m_Position;
    float m_RotationAngle;
    glm::vec3 m_RotationAxis;
    float m_Scale;
};
