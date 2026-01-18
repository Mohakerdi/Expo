// داخل ملف Spotlight.h
#pragma once
#include "Object.h"
#include "Box.h"
#include "Cylinder.h"
#include <glm/glm.hpp>
#include <vector>

class Spotlight : public Object {
public:
    Spotlight();
    ~Spotlight();

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

    Cylinder m_Housing;   // الجسم الخارجي للمبة
    Box m_Lens;            // الزجاج الأمامي
    Cylinder m_Handle;     // المقبض العلوي

    Cylinder m_Base;       // العصا الطويلة
    Cylinder m_Stand;      // القاعدة السفلية

    glm::vec3 m_Position;
    float m_RotationAngle;
    glm::vec3 m_RotationAxis;
    float m_Scale;
};