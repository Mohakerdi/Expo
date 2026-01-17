#include "Expo/AdventureSection.h"
#include "Scene.h"
#include <cstdlib> // For random offsets if needed

AdventureSection::AdventureSection(glm::vec3 origin) : SectionBase(origin) {
    build();
}

AdventureSection::~AdventureSection() {
    cleanup();
}

void AdventureSection::build() {
    // --- THEME: Off-road / Dirt ---

    // 1. Podium (Dirt/Rock Texture)
    Box* podium = new Box(8.0f, 0.5f, 12.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
    podium->setPosition({ m_Origin.x+6.0f, 0.25f, m_Origin.z });
    podium->setAllFacesTexture("assets/textures/plan/p10.jpg"); // Use a rough texture here
    m_Boxes.push_back(podium);

    // 2. Off-road Car (High Clearance)
    ModelObject* car = new ModelObject("assets/obj/race_car_1/scene.gltf", "assets/shaders/model_loading.vert", "assets/shaders/model_loading.frag");
    car->setPosition({ m_Origin.x+6.0f, 1.8f, m_Origin.z });
    car->setRotation(180, { 0, 1, 0 });
    car->setScale(7.0f); // Make it look bigger/heavier
    m_Models.push_back(car);

    // 3. Rocks (Random cubes scattered around)
    for (int i = 0; i < 3; ++i) {
        float offsetX = (i == 0 ? -0.0f : 11.0f);
        float offsetZ = (i * 3.0f) - 2.0f;

        Box* rock = new Box(2.0f, 1.5f, 2.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
        rock->setPosition({ m_Origin.x + offsetX, 0.75f, m_Origin.z + offsetZ });
        rock->setAllFacesTexture("assets/textures/plan/p11.jpg");
        m_Boxes.push_back(rock);
    }

    // 4. Campsite (Simulated Tent)
    Box* tent = new Box(2.5f, 1.5f, 2.5f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
    tent->setPosition({ m_Origin.x , 0.75f, m_Origin.z - 5.0f });
    tent->setAllFacesTexture("assets/textures/plan/p11.jpg"); // Canvas color
    m_Boxes.push_back(tent);
}

void AdventureSection::drawOpaque() {
    for (auto* box : m_Boxes) box->drawOpaque();
    for (auto* cyl : m_Cylinders) cyl->drawOpaque();
    for (auto* model : m_Models) model->drawOpaque();
}

void AdventureSection::drawTransparent() {
    for (auto* box : m_Boxes) box->drawTransparent();
    for (auto* cyl : m_Cylinders) cyl->drawTransparent();
}
void AdventureSection::getTransparent() {
    for (auto* box : m_Boxes) box->getTransparent();
    for (auto* cyl : m_Cylinders) cyl->getTransparent();
}