#include "Expo/HeritageSection.h"
#include "Scene.h"

HeritageSection::HeritageSection(glm::vec3 origin) : SectionBase(origin), m_Car(nullptr) {
    // Initialize m_Car to nullptr
    build();
}

HeritageSection::~HeritageSection() {
    cleanup();

    // <--- PROPER CLEANUP: Delete the car memory
    if (m_Car) {
        delete m_Car;
        m_Car = nullptr;
    }
}

void HeritageSection::build() {
    // --- THEME: Classics / Vintage ---

    // 1. Podium (Wood/Darker Look)
    Box* podium = new Box(8.0f, 0.8f, 12.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
    podium->setPosition({ m_Origin.x, 0.4f, m_Origin.z });
    podium->setAllFacesTexture("assets/textures/plan/p11.jpg"); // Wood
    m_Boxes.push_back(podium);

    m_Car = new PlayerCar();

    // Position it on top of the podium (Y = 0.8 podium height + small offset)
    m_Car->setPosition({ m_Origin.x, 1.0f, m_Origin.z });

    // Rotate 180 degrees to face the front of the room (assuming +Z is front)
    m_Car->setRotation(180.0f, glm::vec3(0, 1, 0));
    m_Car->setScale(2.0f);
    // -----------------------------------------

    // 3. Vintage Gas Pump Simulation (Tall Box)
    Box* gasPump = new Box(1.0f, 3.5f, 1.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
    gasPump->setPosition({ m_Origin.x - 8.0f, 1.75f, m_Origin.z });
    gasPump->setAllFacesTexture("assets/textures/glass.png"); // Red/Brass color
    m_Boxes.push_back(gasPump);

    // 4. Velvet Ropes (Cylinders)
    Cylinder* post1 = new Cylinder(0.1f, 0.1f, 1.0f, 16, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag");
    post1->setPosition({ m_Origin.x - 4.0f, 0.5f, m_Origin.z + 4.0f });
    post1->setSideTexture("assets/textures/plan/p11.jpg");
    m_Cylinders.push_back(post1);

    Cylinder* post2 = new Cylinder(0.1f, 0.1f, 1.0f, 16, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag");
    post2->setPosition({ m_Origin.x + 4.0f, 0.5f, m_Origin.z + 4.0f });
    post2->setSideTexture("assets/textures/plan/p11.jpg");
    m_Cylinders.push_back(post2);
}

void HeritageSection::update(GLFWwindow* window, float dt) {
    // Only update the car if it exists
    if (m_Car) {
        m_Car->UpdateCar(window, dt);
    }
}

void HeritageSection::drawOpaque() {
    // Draw all generic parts
    for (auto* box : m_Boxes) box->drawOpaque();
    for (auto* cyl : m_Cylinders) cyl->drawOpaque();
    for (auto* model : m_Models) model->drawOpaque();

    // <--- DRAW THE NEW CAR
    if (m_Car) m_Car->drawOpaque();
}


void HeritageSection::drawTransparent() {
    for (auto* box : m_Boxes) box->drawTransparent();
    for (auto* cyl : m_Cylinders) cyl->drawTransparent();

    if (m_Car) m_Car->drawTransparent();
}
void HeritageSection::getTransparent() {
    for (auto* box : m_Boxes) box->getTransparent();
    for (auto* cyl : m_Cylinders) cyl->getTransparent();

    if (m_Car) m_Car->getTransparent();
}