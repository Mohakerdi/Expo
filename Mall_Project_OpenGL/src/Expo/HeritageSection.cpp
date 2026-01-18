#include "Expo/HeritageSection.h"
#include "Scene.h"

HeritageSection::HeritageSection(glm::vec3 origin)
    : SectionBase(origin), m_ClassicCar(nullptr)
{
    build();
}

HeritageSection::~HeritageSection() {
    cleanup();

    if (m_ClassicCar) {
        delete m_ClassicCar;
        m_ClassicCar = nullptr;
    }

    for (auto* chair : m_Chairs) {
        delete chair;
    }
    m_Chairs.clear();
}

void HeritageSection::build() {
    Box* podium = new Box(8.0f, 0.8f, 12.0f,
        "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag",
        {}, glm::vec3(0));
    podium->setPosition({ m_Origin.x, 0.4f, m_Origin.z });
    podium->setAllFacesTexture("assets/textures/plan/p11.jpg");
    m_Boxes.push_back(podium);

    // 2. THE CLASSIC CAR - The centerpiece!
    m_ClassicCar = new ClassicCar();
    // Position it on top of the podium (Y = 0.8 podium height + small offset)
    m_ClassicCar->setPosition({ m_Origin.x, 1.2f, m_Origin.z });
    // Rotate to face the front of the room
    m_ClassicCar->setRotation(90.0f, glm::vec3(0, 1, 0));
    m_ClassicCar->setScale(3.0f);  // Nice display size

    // 3. Vintage Gas Pump Simulation (Tall Box)
    Box* gasPump = new Box(1.0f, 3.5f, 1.0f,
        "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag",
        {}, glm::vec3(0));
    gasPump->setPosition({ m_Origin.x - 8.0f, 1.75f, m_Origin.z });
    gasPump->setAllFacesTexture("assets/textures/glass.png");
    m_Boxes.push_back(gasPump);

    // 4. Velvet Ropes (Cylinders) - Exhibition barriers
    Cylinder* post1 = new Cylinder(0.1f, 0.1f, 1.0f, 16,
        "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag");
    post1->setPosition({ m_Origin.x - 4.0f, 0.5f, m_Origin.z + 4.0f });
    post1->setSideTexture("assets/textures/plan/p11.jpg");
    m_Cylinders.push_back(post1);

    Cylinder* post2 = new Cylinder(0.1f, 0.1f, 1.0f, 16,
        "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag");
    post2->setPosition({ m_Origin.x + 4.0f, 0.5f, m_Origin.z + 4.0f });
    post2->setSideTexture("assets/textures/plan/p11.jpg");
    m_Cylinders.push_back(post2);

    // Additional rope posts
    Cylinder* post3 = new Cylinder(0.1f, 0.1f, 1.0f, 16,
        "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag");
    post3->setPosition({ m_Origin.x - 4.0f, 0.5f, m_Origin.z - 4.0f });
    post3->setSideTexture("assets/textures/plan/p11.jpg");
    m_Cylinders.push_back(post3);

    Cylinder* post4 = new Cylinder(0.1f, 0.1f, 1.0f, 16,
        "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag");
    post4->setPosition({ m_Origin.x + 4.0f, 0.5f, m_Origin.z - 4.0f });
    post4->setSideTexture("assets/textures/plan/p11.jpg");
    m_Cylinders.push_back(post4);

    // 5. Viewing Chairs
    float chairZ = m_Origin.z + 8.0f;
    float chairY = 1.8f;

    Chair* chair1 = new Chair();
    chair1->setPosition({ m_Origin.x - 3.5f, chairY, chairZ });
    chair1->setRotation(90.0f, glm::vec3(0, 1, 0));
    chair1->setScale(0.02f);
    m_Chairs.push_back(chair1);

    Chair* chair2 = new Chair();
    chair2->setPosition({ m_Origin.x, chairY, chairZ + 1.5f });
    chair2->setRotation(90.0f, glm::vec3(0, 1, 0));
    chair2->setScale(0.02f);
    m_Chairs.push_back(chair2);

    Chair* chair3 = new Chair();
    chair3->setPosition({ m_Origin.x + 3.5f, chairY, chairZ });
    chair3->setRotation(90.0f, glm::vec3(0, 1, 0));
    chair3->setScale(0.02f);
    m_Chairs.push_back(chair3);

    // 6. Information Plaque
    Box* infoPlaque = new Box(1.5f, 0.8f, 0.1f,
        "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag",
        {}, glm::vec3(0));
    infoPlaque->setPosition({ m_Origin.x + 5.0f, 1.2f, m_Origin.z });
    infoPlaque->setAllFacesTexture("assets/textures/car/info_plaque.jpg");
    m_Boxes.push_back(infoPlaque);
}

void HeritageSection::update(GLFWwindow* window, float dt) {
    // The classic car is a static display piece, no update needed
    // But you could add subtle rotation for a turntable effect:
    // if (m_ClassicCar) {
    //     static float angle = 0.0f;
    //     angle += dt * 5.0f; // Slow rotation
    //     m_ClassicCar->setRotation(angle, glm::vec3(0, 1, 0));
    // }
}

void HeritageSection::drawOpaque() {
    // Draw all generic parts
    for (auto* box : m_Boxes) box->drawOpaque();
    for (auto* cyl : m_Cylinders) cyl->drawOpaque();
    for (auto* model : m_Models) model->drawOpaque();

    // Draw the Classic Car
    if (m_ClassicCar) m_ClassicCar->drawOpaque();

    // Draw the Chairs
    for (auto* chair : m_Chairs) chair->drawOpaque();
}

void HeritageSection::drawTransparent() {
    for (auto* box : m_Boxes) box->drawTransparent();
    for (auto* cyl : m_Cylinders) cyl->drawTransparent();

    if (m_ClassicCar) m_ClassicCar->drawTransparent();

    for (auto* chair : m_Chairs) chair->drawTransparent();
}

void HeritageSection::getTransparent() {
    for (auto* box : m_Boxes) box->getTransparent();
    for (auto* cyl : m_Cylinders) cyl->getTransparent();

    if (m_ClassicCar) m_ClassicCar->getTransparent();

    for (auto* chair : m_Chairs) chair->getTransparent();
}