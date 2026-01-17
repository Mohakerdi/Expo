#include "Expo/VelocitySection.h"
#include "Scene.h"

VelocitySection::VelocitySection(glm::vec3 origin) : SectionBase(origin), m_DrivableCar(nullptr) {
    build();
}

VelocitySection::~VelocitySection() {
    cleanup();

    // <--- CLEAN UP DRIVABLE CAR
    if (m_DrivableCar) {
        delete m_DrivableCar;
        m_DrivableCar = nullptr;
    }
}

void VelocitySection::build() {
    // --- THEME: Speed / Racing ---

    // 1. Podium
    Box* podium = new Box(8.0f, 0.8f, 12.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
    podium->setPosition({ m_Origin.x, m_Origin.y + 0.4f, m_Origin.z });
    podium->setAllFacesTexture("assets/textures/plan/p10.jpg");
    m_Boxes.push_back(podium);

    // 2. Race Car (Static Model)
    ModelObject* car = new ModelObject("assets/obj/race_car_1/scene.gltf", "assets/shaders/model_loading.vert", "assets/shaders/model_loading.frag");
    car->setPosition({ m_Origin.x, m_Origin.y + 2.2f, m_Origin.z });
    car->setScale(7.0f);
    m_Models.push_back(car);

    // 3. <--- ADD DRIVABLE CAR (The new one) ---
    m_DrivableCar = new DrivableCar();

    // Position it beside the model car (e.g., to the right on X axis)
    // It needs to be on the ground (Y=0.5f)
    m_DrivableCar->setPosition({ m_Origin.x + 8.0f, 0.5f, m_Origin.z });

    // Rotate it 180 degrees to face the same way as the model car (assuming model faces back)
    m_DrivableCar->setRotation(180.0f, glm::vec3(0, 1, 0));
    // ------------------------------------

    // 4. Stack of Tires (Cylinders)
    float tireX = m_Origin.x + 15.0f; // Moved further right to avoid collision with drivable car
    float tireZ = m_Origin.z - 5.0f;
    float tireR = 1.0f;
    float tireH = 0.8f;

    for (int i = 0; i < 3; ++i) {
        Cylinder* tire = new Cylinder(tireR, tireR, tireH, 32, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag");
        tire->setPosition({ tireX, 0.4f + (i * tireH) + m_Origin.y + 0.4f, tireZ });
        tire->setSideTexture("assets/textures/wheel1.jpg");
        tire->setTopTexture("assets/textures/wheel2.png");
        tire->setBottomTexture("assets/textures/wheel2.png");
        m_Cylinders.push_back(tire);
    }

    // 5. Wind Tunnel (Glass Box)
    Box* windTunnel = new Box(6.0f, 4.0f, 8.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
    windTunnel->setPosition({ m_Origin.x - 8.0f, 2.0f, m_Origin.z + 5.0f });
    windTunnel->setAllFacesTexture("assets/textures/glass.png", true);
    m_Boxes.push_back(windTunnel);
}

void VelocitySection::drawOpaque() {
    for (auto* box : m_Boxes) box->drawOpaque();
    for (auto* cyl : m_Cylinders) cyl->drawOpaque();
    for (auto* model : m_Models) model->drawOpaque();

    // <--- DRAW DRIVABLE CAR
    if (m_DrivableCar) m_DrivableCar->drawOpaque();
}

void VelocitySection::drawTransparent() {
    for (auto* box : m_Boxes) box->drawTransparent();
    for (auto* cyl : m_Cylinders) cyl->drawTransparent();

    // <--- DRAW DRIVABLE CAR GLASS
    if (m_DrivableCar) m_DrivableCar->drawTransparent();
}

// <--- ADD UPDATE FUNCTION
void VelocitySection::update(GLFWwindow* window, float dt) {
    if (m_DrivableCar) {
        m_DrivableCar->UpdateCar(window, dt);
    }
}

// <--- ADD GET TRANSPARENT FUNCTION
void VelocitySection::getTransparent() {
    for (auto* box : m_Boxes) box->getTransparent();
    for (auto* cyl : m_Cylinders) cyl->getTransparent();

    if (m_DrivableCar) m_DrivableCar->getTransparent();
}