#include "Expo/Poster.h"
#include <glm/gtc/matrix_transform.hpp>

// استقبل العرض والارتفاع هنا
Poster::Poster(std::string texturePath, float width, float height)
// استخدم المتغيرات width و height في إنشاء الـ Box
    : m_Plane(width, height, 0.2f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_TexturePath(texturePath)
{
    m_Position = { 0.0f, 0.0f, 0.0f };
    m_RotationAngle = 0.0f;
    m_RotationAxis = { 0.0f, 1.0f, 0.0f };
    m_Scale = 1.0f;

    setTex(); // استدعاء دالة تعيين التكستشر المخصصة
}

Poster::~Poster() {}

void Poster::setPosition(const glm::vec3& pos) { m_Position = pos; }
void Poster::setRotation(float angle, const glm::vec3& axis) { m_RotationAngle = angle; m_RotationAxis = axis; }
void Poster::setScale(float s) { m_Scale = s; }

glm::mat4 Poster::getModelMatrix() {
    glm::mat4 model(1.0f);
    model = glm::translate(model, m_Position);
    model = glm::rotate(model, glm::radians(m_RotationAngle), m_RotationAxis);
    model = glm::scale(model, glm::vec3(m_Scale));
    return model;
}

void Poster::update(float dt) { (void)dt; }

void Poster::drawOpaque() {
    updateModelMatrix();
    m_Plane.setParentModel(getModelMatrix());
    m_Plane.setPosition({ 0.0f, 0.0f, 0.0f });
    m_Plane.drawOpaque();
}
void Poster::drawTransparent() {}
void Poster::getTransparent() {}
void Poster::onImguiRender() {}

// دالة جديدة لتعيين التكستشر بدقة
void Poster::setTex()
{
    std::string backTexture = "assets/textures/interiors/wood_dark.jpg"; // لون الخلفية (خشب أو رمادي)

    // 1. الصورة تظهر على الوجه الأمامي فقط
    m_Plane.setFaceTexture(Face::Front, m_TexturePath);

    // 2. بقية الأوجه (الخلف، الجوانب، الأعلى، الأسفل) بلون موحد أو خشب
    m_Plane.setFaceTexture(Face::Back, backTexture);
    m_Plane.setFaceTexture(Face::Up, backTexture);
    m_Plane.setFaceTexture(Face::Down, backTexture);
    m_Plane.setFaceTexture(Face::Left, backTexture);
    m_Plane.setFaceTexture(Face::Right, backTexture);
}