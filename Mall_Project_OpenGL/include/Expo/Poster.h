#pragma once
#include "Object.h"
#include "Box.h"
#include <glm/glm.hpp>
#include <string>

class Poster : public Object {
public:
    // أضفنا width و height كمعاملات
    Poster(std::string texturePath, float width = 20.0f, float height = 15.0f);
    ~Poster();

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

    Box m_Plane;
    std::string m_TexturePath;

    glm::vec3 m_Position;
    float m_RotationAngle;
    glm::vec3 m_RotationAxis;
    float m_Scale;
};