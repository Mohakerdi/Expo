#include "Expo/Car/JeepCar.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

JeepCar::JeepCar()
// Body Initialization
    : m_BodyMain(3.0f, 1.2f, 4.5f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_BodyFront(2.8f, 0.6f, 1.8f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_BodyRear(2.8f, 1.3f, 1.6f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_BodyRoof(2.65f, 0.1f, 3.3f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),

    // Bumpers
    m_BumperFront(3.2f, 0.3f, 0.4f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_BumperRear(3.2f, 0.3f, 0.4f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),

    // Windows
    m_Windshield(2.35f, 1.1f, 0.1f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_SideWindowL(0.1f, 0.95f, 2.4f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_SideWindowR(0.1f, 0.95f, 2.4f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_RearWindow(2.15f, 0.9f, 0.1f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),

    // Lights
    m_Grill(2.0f, 0.5f, 0.1f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_HeadlightL(0.5f, 0.3f, 0.1f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_HeadlightR(0.5f, 0.3f, 0.1f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_TaillightL(0.4f, 0.3f, 0.1f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_TaillightR(0.4f, 0.3f, 0.1f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),

    // Tires
    m_WheelFL(0.75f, 0.75f, 0.55f, 24, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_WheelFR(0.75f, 0.75f, 0.55f, 24, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_WheelBL(0.75f, 0.75f, 0.55f, 24, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_WheelBR(0.75f, 0.75f, 0.55f, 24, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),

    // Rims
    m_RimFL(0.4f, 0.4f, 0.45f, 16, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_RimFR(0.4f, 0.4f, 0.45f, 16, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_RimBL(0.4f, 0.4f, 0.45f, 16, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_RimBR(0.4f, 0.4f, 0.45f, 16, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),

    // Spare Tire
    m_SpareTire(0.75f, 0.75f, 0.55f, 24, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_SpareTireRim(0.4f, 0.4f, 0.45f, 16, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag")
{
    m_Position = { 0.0f, 0.75f, 0.0f };
    m_Scale = 1.0f;
    setTextures();
}

void JeepCar::setPosition(const glm::vec3& pos) { m_Position = pos; }
void JeepCar::setRotation(float angle, const glm::vec3& axis) { m_RotationAngle = angle; m_RotationAxis = axis; }
void JeepCar::setScale(float s) { m_Scale = s; }

glm::mat4 JeepCar::getModelMatrix() {
    glm::mat4 model(1.0f);
    model = glm::translate(model, m_Position);
    model = glm::rotate(model, glm::radians(m_RotationAngle), m_RotationAxis);
    model = glm::scale(model, glm::vec3(m_Scale));
    return model;
}

void JeepCar::setTextures() {
    // --- تعريف الألوان والنصوص (Textures) ---
    std::string bodyPaint = "assets/textures/car/yellow_metal.png";

    // لون المصدات والشبك (رمادي غامق معدني)
    std::string darkMetal = "assets/textures/car/dark_grey_metal.jpg";

    // لون النوافذ الصلبة (منفصل عن المصدات) - يمكن استخدام صورة زجاج غير شفاف
    std::string solidWindowColor = "assets/textures/car/glass.png";

    std::string chrome = "assets/textures/car/wheel.png";
    std::string rubber = "assets/textures/car/rubber_tire.png";
    std::string redLight = "assets/textures/car/red_light.jpg";
    std::string whiteLight = "assets/textures/car/white_light.jpg";

    // --- Body Parts ---
    m_BodyMain.setAllFacesTexture(bodyPaint);
    m_BodyFront.setAllFacesTexture(bodyPaint);
    m_BodyRear.setAllFacesTexture(bodyPaint);
    m_BodyRoof.setAllFacesTexture(darkMetal); // السقف بنفس لون المعدن

    // --- Bumpers & Grill (لون منفصل) ---
    m_BumperFront.setAllFacesTexture(darkMetal);
    m_BumperRear.setAllFacesTexture(darkMetal);
    m_Grill.setAllFacesTexture(darkMetal);

    // --- Lights ---
    m_HeadlightL.setAllFacesTexture(whiteLight);
    m_HeadlightR.setAllFacesTexture(whiteLight);
    m_TaillightL.setAllFacesTexture(redLight);
    m_TaillightR.setAllFacesTexture(redLight);

    // --- النوافذ (الآن بلون منفصل) ---
    m_Windshield.setAllFacesTexture(solidWindowColor, false);
    m_SideWindowL.setAllFacesTexture(solidWindowColor, false);
    m_SideWindowR.setAllFacesTexture(solidWindowColor, false);
    m_RearWindow.setAllFacesTexture(solidWindowColor, false);

    // --- Wheels ---
    // الإطارات المطاطية
    m_WheelFL.setSideTexture(rubber);
    m_WheelFR.setSideTexture(rubber);
    m_WheelBL.setSideTexture(rubber);
    m_WheelBR.setSideTexture(rubber);
    m_SpareTire.setSideTexture(rubber);

    // الجنوط المعدنية
    m_RimFL.setSideTexture(chrome);
    m_RimFR.setSideTexture(chrome);
    m_RimBL.setSideTexture(chrome);
    m_RimBR.setSideTexture(chrome);
    m_SpareTireRim.setSideTexture(chrome);
}

void JeepCar::update(float dt) { (void)dt; }

void JeepCar::drawOpaque() {
    glm::mat4 root = getModelMatrix();

    // 1. Body
    m_BodyMain.setParentModel(root);
    m_BodyMain.setPosition({ 0.0f, 0.6f, 0.0f });
    m_BodyMain.drawOpaque();

    m_BodyFront.setParentModel(root);
    m_BodyFront.setPosition({ 0.0f, 1.1f, 2.1f });
    m_BodyFront.drawOpaque();

    m_BodyRear.setParentModel(root);
    m_BodyRear.setPosition({ 0.0f, 1.1f, -1.9f });
    m_BodyRear.drawOpaque();

    m_BodyRoof.setParentModel(root);
    m_BodyRoof.setPosition({ 0.0f, 2.05f, -0.3f });
    m_BodyRoof.drawOpaque();

    // Accessories
    m_BumperFront.setParentModel(root);
    m_BumperFront.setPosition({ 0.0f, 0.4f, 3.1f });
    m_BumperFront.drawOpaque();

    m_BumperRear.setParentModel(root);
    m_BumperRear.setPosition({ 0.0f, 0.4f, -2.9f });
    m_BumperRear.drawOpaque();

    m_Grill.setParentModel(root);
    m_Grill.setPosition({ 0.0f, 1.0f, 3.05f });
    m_Grill.drawOpaque(); // تم تصحيح الخطأ (كان BumperFront)

    m_HeadlightL.setParentModel(root);
    m_HeadlightL.setPosition({ -0.9f, 1.0f, 3.06f });
    m_HeadlightL.drawOpaque();

    m_HeadlightR.setParentModel(root);
    m_HeadlightR.setPosition({ 0.9f, 1.0f, 3.06f });
    m_HeadlightR.drawOpaque();

    m_TaillightL.setParentModel(root);
    m_TaillightL.setPosition({ -1.0f, 1.2f, -2.96f });
    m_TaillightL.drawOpaque();

    m_TaillightR.setParentModel(root);
    m_TaillightR.setPosition({ 1.0f, 1.2f, -2.96f });
    m_TaillightR.drawOpaque();

    // 2. Windows (Solid) - بلون منفصل
    m_Windshield.setParentModel(root);
    m_Windshield.setPosition({ 0.0f, 1.55f, 1.25f });
    m_Windshield.setRotation(-35.0f, { 1,0,0 });
    m_Windshield.drawOpaque();

    m_SideWindowL.setParentModel(root);
    m_SideWindowL.setPosition({ -1.35f, 1.8f, -0.3f });
    m_SideWindowL.drawOpaque();

    m_SideWindowR.setParentModel(root);
    m_SideWindowR.setPosition({ 1.35f, 1.8f, -0.3f });
    m_SideWindowR.drawOpaque();

    m_RearWindow.setParentModel(root);
    m_RearWindow.setPosition({ 0.0f, 1.8f, -2.55f });
    m_RearWindow.setRotation(10.0f, { 1,0,0 });
    m_RearWindow.drawOpaque();

    // 3. Wheels
    float wheelX = 1.6f;
    float wheelZ = 2.0f;
    float wheelY = 0.0f;

    auto drawWheel = [&root, wheelY](Cylinder& tire, Cylinder& rim, float x, float z) {
        tire.setParentModel(root);
        tire.setPosition({ x, wheelY, z });
        tire.setRotation(90, { 0,0,1 });
        tire.drawOpaque();

        rim.setParentModel(root);
        rim.setPosition({ x, wheelY, z });
        rim.setRotation(90, { 0,0,1 });
        rim.drawOpaque();
        };

    drawWheel(m_WheelFL, m_RimFL, -wheelX, wheelZ);
    drawWheel(m_WheelFR, m_RimFR, wheelX, wheelZ);
    drawWheel(m_WheelBL, m_RimBL, -wheelX, -wheelZ);
    drawWheel(m_WheelBR, m_RimBR, wheelX, -wheelZ);

    // Spare Tire
    m_SpareTire.setParentModel(root);
    m_SpareTire.setPosition({ 0.0f, 1.2f, -3.0f });
    m_SpareTire.setRotation(90, { 1,0,0 });
    m_SpareTire.drawOpaque();

    m_SpareTireRim.setParentModel(root);
    m_SpareTireRim.setPosition({ 0.0f, 1.2f, -3.0f });
    m_SpareTireRim.setRotation(90, { 1,0,0 });
    m_SpareTireRim.drawOpaque();
}

void JeepCar::drawTransparent() {
    // فارغ
}