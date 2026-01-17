#include "Expo/InnovationSection.h"
#include "Scene.h"

InnovationSection::InnovationSection(glm::vec3 origin) : SectionBase(origin) {
    build();
}

InnovationSection::~InnovationSection() {
    cleanup(); // Calls base class cleanup
}

void InnovationSection::build() {
    // --- THEME: High Tech / Electric ---

    // 1. Podium (Polished Concrete look)
    Box* podium = new Box(8.0f, 0.8f, 12.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
    podium->setPosition({ m_Origin.x - 6.0f, 0.4f, m_Origin.z });
    podium->setRotation(45, { 0, 1, 0 });
    podium->setAllFacesTexture("assets/textures/plan/p10.jpg"); // Smooth floor
    m_Boxes.push_back(podium);

    // 2. Main Car (Electric Concept)
    ModelObject* car = new ModelObject("assets/obj/race_car_1/scene.gltf", "assets/shaders/model_loading.vert", "assets/shaders/model_loading.frag");
    car->setPosition({ m_Origin.x - 6.0f, 2.4f, m_Origin.z });
    car->setRotation(45, { 0, 1, 0 });
    car->setScale(7.0f);
    m_Models.push_back(car);

    // 3. Holographic Screens (Info Panels)
    Box* screenLeft = new Box(1.5f, 3.0f, 0.2f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
    screenLeft->setPosition({ m_Origin.x - 12.0f, 1.5f, m_Origin.z + 5.0f });
    screenLeft->setAllFacesTexture("assets/textures/car_paint.jpg", false); // Glowing glass look
    m_Boxes.push_back(screenLeft);

    Box* screenRight = new Box(1.5f, 3.0f, 0.2f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
    screenRight->setPosition({ m_Origin.x , 1.5f, m_Origin.z - 5.0f });
    screenRight->setAllFacesTexture("assets/textures/car_paint.jpg", false);
    m_Boxes.push_back(screenRight);
}

void InnovationSection::drawOpaque() {
    for (auto* box : m_Boxes) box->drawOpaque();
    for (auto* cyl : m_Cylinders) cyl->drawOpaque();
    for (auto* model : m_Models) model->drawOpaque();
}

void InnovationSection::drawTransparent() {
    for (auto* box : m_Boxes) box->drawTransparent();
    for (auto* cyl : m_Cylinders) cyl->drawTransparent();
}
void InnovationSection::getTransparent() {
    for (auto* box : m_Boxes) box->getTransparent();
    for (auto* cyl : m_Cylinders) cyl->getTransparent();
}
