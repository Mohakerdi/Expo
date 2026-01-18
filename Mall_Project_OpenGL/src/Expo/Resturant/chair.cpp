#include "Expo/Resturant/Chair.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Chair::Chair()
// Seat
    : m_Seat(80.0f, 10.0f, 80.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),

    // Backrest
    m_Backrest(70.0f, 70.0f, 10.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),

    // Armrests
    m_ArmrestL(10.0f, 50.0f, 70.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_ArmrestR(10.0f, 50.0f, 70.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),

    // Legs (تم تعريفهم هنا بشكل منفصل مثل Table)
    m_LegFL(5.0f, 5.0f, 65.0f, 24, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_LegFR(5.0f, 5.0f, 65.0f, 24, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_LegBL(5.0f, 5.0f, 65.0f, 24, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_LegBR(5.0f, 5.0f, 65.0f, 24, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag")
{
    m_Position = { 0.0f, 0.0f, 0.0f };
    m_RotationAngle = 0.0f;
    m_RotationAxis = { 0.0f, 1.0f, 0.0f };
    m_Scale = 1.0f;
    setTex();
}

Chair::~Chair() {
}

void Chair::setPosition(const glm::vec3& pos) { m_Position = pos; }
void Chair::setRotation(float angle, const glm::vec3& axis) { m_RotationAngle = angle; m_RotationAxis = axis; }
void Chair::setScale(float s) { m_Scale = s; }

glm::mat4 Chair::getModelMatrix() {
    glm::mat4 model(1.0f);
    model = glm::translate(model, m_Position);
    model = glm::rotate(model, glm::radians(m_RotationAngle), m_RotationAxis);
    model = glm::scale(model, glm::vec3(m_Scale));
    return model;
}

void Chair::setTex()
{
    // --- خامة المقعد والظهر والذراعين (Boxes) ---
    std::string woodTexture = "assets/textures/oh.png";
    std::string metalTexture = "assets/textures/awesomeface.png";

    m_Seat.setAllFacesTexture(woodTexture);
    m_Backrest.setAllFacesTexture(woodTexture);
    m_ArmrestL.setAllFacesTexture(woodTexture);
    m_ArmrestR.setAllFacesTexture(woodTexture);

    // --- خامة الأرجل (Cylinders) ---
    // استخدام setSideTexture فقط لتجنب الأخطاء
    m_LegFL.setSideTexture(metalTexture);
    m_LegFR.setSideTexture(metalTexture);
    m_LegBL.setSideTexture(metalTexture);
    m_LegBR.setSideTexture(metalTexture);
}

void Chair::update(float dt) {
    (void)dt;
}

void Chair::drawOpaque() {
    updateModelMatrix();
    glm::mat4 root = getModelMatrix();

    // إعداد الموديل الأساسي لكل الأجزاء
    m_Seat.setParentModel(root);
    m_Backrest.setParentModel(root);
    m_ArmrestL.setParentModel(root);
    m_ArmrestR.setParentModel(root);
    m_LegFL.setParentModel(root);
    m_LegFR.setParentModel(root);
    m_LegBL.setParentModel(root);
    m_LegBR.setParentModel(root);

    // أبعاد الكرسي للإحداثيات
    float width = 80.0f;   // عرض المقعد
    float depth = 80.0f;   // عمق المقعد
    float legHeight = 65.0f;
    float seatHeight = 10.0f; // ارتفاع المقعد

    // حساب إحداثيات الأرجل لتكون تحت المقعد
    float xOff = width / 2.0f - 10.0f; // 40 - 10 = 30
    float zOff = depth / 2.0f - 10.0f;
    float yPos = -(legHeight / 2.0f) + (seatHeight / 2.0f);

    // رسم الأرجل
    m_LegFL.setPosition({ -xOff, yPos, -zOff }); // Front Left
    m_LegFL.drawOpaque();

    m_LegFR.setPosition({ xOff, yPos, -zOff });  // Front Right
    m_LegFR.drawOpaque();

    m_LegBL.setPosition({ -xOff, yPos, zOff });  // Back Left
    m_LegBL.drawOpaque();

    m_LegBR.setPosition({ xOff, yPos, zOff });   // Back Right
    m_LegBR.drawOpaque();

    // رسم المقعد
    m_Seat.setPosition({ 0.0f, 0.0f, 0.0f });
    m_Seat.drawOpaque();

    // رسم مسند الظهر (خلف المقعد)
    m_Backrest.setPosition({ 0.0f, 35.0f, -40.0f });
    m_Backrest.setRotation(-10.0f, { 1, 0, 0 });
    m_Backrest.drawOpaque();

    // رسم مسندات الذراعين
    m_ArmrestL.setPosition({ -45.0f, 25.0f, 0.0f });
    m_ArmrestL.drawOpaque();

    m_ArmrestR.setPosition({ 45.0f, 25.0f, 0.0f });
    m_ArmrestR.drawOpaque();
}

void Chair::drawTransparent() {
    // فارغ
}

void Chair::getTransparent() {
    m_Seat.setParentModel(getModel());
    m_LegFL.setParentModel(getModel());
    m_LegFR.setParentModel(getModel());
    m_LegBL.setParentModel(getModel());
    m_LegBR.setParentModel(getModel());

    float width = 80.0f;
    float depth = 80.0f;
    float legHeight = 65.0f;
    float seatHeight = 10.0f;

    float xOff = width / 2.0f - 10.0f;
    float zOff = depth / 2.0f - 10.0f;
    float yPos = -(legHeight / 2.0f) + (seatHeight / 2.0f);

    m_LegFL.setPosition({ -xOff, yPos, -zOff });
    m_LegFL.getTransparent();

    m_LegFR.setPosition({ xOff, yPos, -zOff });
    m_LegFR.getTransparent();

    m_LegBL.setPosition({ -xOff, yPos, zOff });
    m_LegBL.getTransparent();

    m_LegBR.setPosition({ xOff, yPos, zOff });
    m_LegBR.getTransparent();

    m_Seat.setPosition({ 0.0f, 0.0f, 0.0f });
    m_Seat.getTransparent();
}

void Chair::onImguiRender()
{
    ImGui::SliderFloat3("Chair Position", &m_Position.x, -100, 100);
}