#include "Expo/Teble.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Table::Table()
// Table Top (Surface)
    : m_TableTop(120.0f, 5.0f, 70.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),

    // Legs (Radius, Radius, Height, Segments, Vert, Frag)
    m_LegFL(4.0f, 4.0f, 60.0f, 24, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_LegFR(4.0f, 4.0f, 60.0f, 24, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_LegBL(4.0f, 4.0f, 60.0f, 24, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_LegBR(4.0f, 4.0f, 60.0f, 24, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag")
{
    m_Position = { 0.0f, 0.0f, 0.0f };
    m_RotationAngle = 0.0f;
    m_RotationAxis = { 0.0f, 1.0f, 0.0f };
    m_Scale = 1.0f;
    setTextures();
}

Table::~Table() {
}

void Table::setPosition(const glm::vec3& pos) { m_Position = pos; }
void Table::setRotation(float angle, const glm::vec3& axis) { m_RotationAngle = angle; m_RotationAxis = axis; }
void Table::setScale(float s) { m_Scale = s; }

glm::mat4 Table::getModelMatrix() {
    glm::mat4 model(1.0f);
    model = glm::translate(model, m_Position);
    model = glm::rotate(model, glm::radians(m_RotationAngle), m_RotationAxis);
    // تم تصحيح Error glm::scale هنا
    model = glm::scale(model, glm::vec3(m_Scale));
    return model;
}

void Table::setTextures() {
    // --- تعريف مسارات الصور ---
    std::string woodTexture = "assets/textures/oh.png";
    std::string metalTexture = "assets/textures/awesomeface.png";

    // --- السطح ---
    m_TableTop.setAllFacesTexture(woodTexture);

    // --- الأرجل ---
    // جوانب الاسطوانات فقط (تم حذف setFaceTexture لإصلاح Error)
    m_LegFL.setSideTexture(metalTexture);
    m_LegFR.setSideTexture(metalTexture);
    m_LegBL.setSideTexture(metalTexture);
    m_LegBR.setSideTexture(metalTexture);

    // تم حذف استدعاء setFaceTexture لأن Cylinder لا يدعمها في مشروعك
}

void Table::update(float dt) {
    (void)dt;
}

void Table::drawOpaque() {
    glm::mat4 root = getModelMatrix();

    // إعداد الموديل الأساسي
    m_TableTop.setParentModel(root);
    m_LegFL.setParentModel(root);
    m_LegFR.setParentModel(root);
    m_LegBL.setParentModel(root);
    m_LegBR.setParentModel(root);

    // أبعاد الطاولة للإحداثيات
    float width = 120.0f;
    float depth = 70.0f;
    float legHeight = 60.0f;
    float topHeight = 5.0f;

    // حساب إحداثيات الأرجل لتكون تحت السطح
    float xOff = width / 2.0f - 5.0f;
    float zOff = depth / 2.0f - 5.0f;
    float yPos = -(legHeight / 2.0f) + (topHeight / 2.0f);

    // رسم الأرجل
    m_LegFL.setPosition({ -xOff, yPos, -zOff });
    m_LegFL.drawOpaque();

    m_LegFR.setPosition({ xOff, yPos, -zOff });
    m_LegFR.drawOpaque();

    m_LegBL.setPosition({ -xOff, yPos, zOff });
    m_LegBL.drawOpaque();

    m_LegBR.setPosition({ xOff, yPos, zOff });
    m_LegBR.drawOpaque();

    // رسم السطح
    m_TableTop.setPosition({ 0.0f, 0.0f, 0.0f });
    m_TableTop.drawOpaque();
}

void Table::drawTransparent() {
    // فارغ
}