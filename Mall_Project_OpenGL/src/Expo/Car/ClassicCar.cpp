#include "Expo/Car/ClassicCar.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

ClassicCar::ClassicCar()
    : m_SteeringColumn(nullptr),
    m_SteeringWheelRim(nullptr)
{
    build();
}

ClassicCar::~ClassicCar() {
    cleanup();
}

void ClassicCar::cleanup() {
    // Clean up body boxes
    for (auto* box : m_BodyBoxes) {
        delete box;
    }
    m_BodyBoxes.clear();

    // Clean up body cylinders
    for (auto* cyl : m_BodyCylinders) {
        delete cyl;
    }
    m_BodyCylinders.clear();

    // Clean up wheels
    for (auto* wheel : m_Wheels) {
        delete wheel;
    }
    m_Wheels.clear();

    for (auto* hub : m_WheelHubs) {
        delete hub;
    }
    m_WheelHubs.clear();

    // Clean up interior
    for (auto* box : m_InteriorBoxes) {
        delete box;
    }
    m_InteriorBoxes.clear();

    for (auto* cyl : m_InteriorCylinders) {
        delete cyl;
    }
    m_InteriorCylinders.clear();

    // Clean up windows
    for (auto* window : m_Windows) {
        delete window;
    }
    m_Windows.clear();

    // Clean up lights
    for (auto* light : m_Lights) {
        delete light;
    }
    m_Lights.clear();

    // Clean up mirrors
    for (auto* mirror : m_Mirrors) {
        delete mirror;
    }
    m_Mirrors.clear();

    // Clean up steering wheel
    if (m_SteeringColumn) {
        delete m_SteeringColumn;
        m_SteeringColumn = nullptr;
    }
    if (m_SteeringWheelRim) {
        delete m_SteeringWheelRim;
        m_SteeringWheelRim = nullptr;
    }
    for (auto* spoke : m_SteeringSpokes) {
        delete spoke;
    }
    m_SteeringSpokes.clear();

    // Clean up gauges
    for (auto* gauge : m_Gauges) {
        delete gauge;
    }
    m_Gauges.clear();

    // Clean up seats
    for (auto* seat : m_Seats) {
        delete seat;
    }
    m_Seats.clear();

    // Clean up exhaust pipes
    for (auto* pipe : m_ExhaustPipes) {
        delete pipe;
    }
    m_ExhaustPipes.clear();

    // Clean up bumpers
    for (auto* bumper : m_Bumpers) {
        delete bumper;
    }
    m_Bumpers.clear();

    // Clean up door handles
    for (auto* handle : m_DoorHandles) {
        delete handle;
    }
    m_DoorHandles.clear();

    // Clean up grille
    for (auto* grillePart : m_Grille) {
        delete grillePart;
    }
    m_Grille.clear();
}

void ClassicCar::build() {
    // ============================================
    // CLASSIC CAR DIMENSIONS (in local units)
    // ============================================
    // Total length: ~4.5 units
    // Total width: ~1.8 units  
    // Total height: ~1.4 units

    float carLength = 4.5f;
    float carWidth = 1.8f;
    float carHeight = 0.6f;  // Main body height
    float cabinHeight = 0.7f;
    float groundClearance = 0.3f;

    // ============================================
    // 1. MAIN BODY / CHASSIS
    // ============================================

    // Main body block (lower body)
    Box* mainBody = new Box(carLength, carHeight, carWidth, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    mainBody->setPosition({ 0.0f, groundClearance + carHeight / 2, 0.0f });
    mainBody->setAllFacesTexture("assets/textures/car/classic_red.jpg"); // Deep red classic color
    m_BodyBoxes.push_back(mainBody);

    // Hood (front engine compartment)
    Box* hood = new Box(1.5f, 0.3f, carWidth - 0.1f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    hood->setPosition({ 1.3f, groundClearance + carHeight + 0.15f, 0.0f });
    hood->setAllFacesTexture("assets/textures/car/classic_red.jpg");
    m_BodyBoxes.push_back(hood);

    // Trunk (rear)
    Box* trunk = new Box(1.0f, 0.25f, carWidth - 0.1f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    trunk->setPosition({ -1.5f, groundClearance + carHeight + 0.125f, 0.0f });
    trunk->setAllFacesTexture("assets/textures/car/classic_red.jpg");
    m_BodyBoxes.push_back(trunk);

    // ============================================
    // 2. CABIN / PASSENGER COMPARTMENT
    // ============================================

    // Cabin base
    Box* cabinBase = new Box(1.8f, 0.1f, carWidth - 0.2f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    cabinBase->setPosition({ -0.1f, groundClearance + carHeight + 0.05f, 0.0f });
    cabinBase->setAllFacesTexture("assets/textures/car/interior_brown.jpg"); // Brown leather interior
    m_InteriorBoxes.push_back(cabinBase);

    // Cabin pillars (A-pillar front left)
    Box* pillarFL = new Box(0.1f, cabinHeight, 0.1f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    pillarFL->setPosition({ 0.7f, groundClearance + carHeight + cabinHeight / 2, carWidth / 2 - 0.1f });
    pillarFL->setAllFacesTexture("assets/textures/car/chrome.jpg");
    m_BodyBoxes.push_back(pillarFL);

    // A-pillar front right
    Box* pillarFR = new Box(0.1f, cabinHeight, 0.1f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    pillarFR->setPosition({ 0.7f, groundClearance + carHeight + cabinHeight / 2, -carWidth / 2 + 0.1f });
    pillarFR->setAllFacesTexture("assets/textures/car/chrome.jpg");
    m_BodyBoxes.push_back(pillarFR);

    // B-pillar (center) left
    Box* pillarCL = new Box(0.08f, cabinHeight, 0.08f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    pillarCL->setPosition({ -0.1f, groundClearance + carHeight + cabinHeight / 2, carWidth / 2 - 0.1f });
    pillarCL->setAllFacesTexture("assets/textures/car/chrome.jpg");
    m_BodyBoxes.push_back(pillarCL);

    // B-pillar center right
    Box* pillarCR = new Box(0.08f, cabinHeight, 0.08f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    pillarCR->setPosition({ -0.1f, groundClearance + carHeight + cabinHeight / 2, -carWidth / 2 + 0.1f });
    pillarCR->setAllFacesTexture("assets/textures/car/chrome.jpg");
    m_BodyBoxes.push_back(pillarCR);

    // C-pillar (rear) left
    Box* pillarRL = new Box(0.1f, cabinHeight, 0.1f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    pillarRL->setPosition({ -0.9f, groundClearance + carHeight + cabinHeight / 2, carWidth / 2 - 0.1f });
    pillarRL->setAllFacesTexture("assets/textures/car/chrome.jpg");
    m_BodyBoxes.push_back(pillarRL);

    // C-pillar rear right
    Box* pillarRR = new Box(0.1f, cabinHeight, 0.1f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    pillarRR->setPosition({ -0.9f, groundClearance + carHeight + cabinHeight / 2, -carWidth / 2 + 0.1f });
    pillarRR->setAllFacesTexture("assets/textures/car/chrome.jpg");
    m_BodyBoxes.push_back(pillarRR);

    // Roof
    Box* roof = new Box(1.7f, 0.08f, carWidth - 0.15f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    roof->setPosition({ -0.1f, groundClearance + carHeight + cabinHeight + 0.04f, 0.0f });
    roof->setAllFacesTexture("assets/textures/car/classic_red.jpg");
    m_BodyBoxes.push_back(roof);

    // ============================================
    // 3. WINDOWS (TRANSPARENT)
    // ============================================

    // Windshield (front)
    Box* windshield = new Box(0.05f, cabinHeight - 0.15f, carWidth - 0.3f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    windshield->setPosition({ 0.72f, groundClearance + carHeight + cabinHeight / 2 + 0.05f, 0.0f });
    windshield->setRotation(15.0f, glm::vec3(0, 0, 1)); // Slight angle
    windshield->setAllFacesTexture("assets/textures/car/glass_tint.png");
    m_Windows.push_back(windshield);

    // Rear window
    Box* rearWindow = new Box(0.05f, cabinHeight - 0.2f, carWidth - 0.35f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    rearWindow->setPosition({ -0.92f, groundClearance + carHeight + cabinHeight / 2 + 0.05f, 0.0f });
    rearWindow->setRotation(-15.0f, glm::vec3(0, 0, 1));
    rearWindow->setAllFacesTexture("assets/textures/car/glass_tint.png");
    m_Windows.push_back(rearWindow);

    // Side windows (left front)
    Box* sideWindowLF = new Box(0.6f, cabinHeight - 0.25f, 0.03f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    sideWindowLF->setPosition({ 0.3f, groundClearance + carHeight + cabinHeight / 2 + 0.08f, carWidth / 2 - 0.05f });
    sideWindowLF->setAllFacesTexture("assets/textures/car/glass_tint.png");
    m_Windows.push_back(sideWindowLF);

    // Side windows (left rear)
    Box* sideWindowLR = new Box(0.6f, cabinHeight - 0.25f, 0.03f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    sideWindowLR->setPosition({ -0.5f, groundClearance + carHeight + cabinHeight / 2 + 0.08f, carWidth / 2 - 0.05f });
    sideWindowLR->setAllFacesTexture("assets/textures/car/glass_tint.png");
    m_Windows.push_back(sideWindowLR);

    // Side windows (right front)
    Box* sideWindowRF = new Box(0.6f, cabinHeight - 0.25f, 0.03f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    sideWindowRF->setPosition({ 0.3f, groundClearance + carHeight + cabinHeight / 2 + 0.08f, -carWidth / 2 + 0.05f });
    sideWindowRF->setAllFacesTexture("assets/textures/car/glass_tint.png");
    m_Windows.push_back(sideWindowRF);

    // Side windows (right rear)
    Box* sideWindowRR = new Box(0.6f, cabinHeight - 0.25f, 0.03f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    sideWindowRR->setPosition({ -0.5f, groundClearance + carHeight + cabinHeight / 2 + 0.08f, -carWidth / 2 + 0.05f });
    sideWindowRR->setAllFacesTexture("assets/textures/car/glass_tint.png");
    m_Windows.push_back(sideWindowRR);

    // ============================================
    // 4. WHEELS (4 wheels with hubs)
    // ============================================

    float wheelRadius = 0.35f;
    float wheelWidth = 0.15f;
    float wheelX_front = 1.3f;
    float wheelX_rear = -1.3f;
    float wheelZ = carWidth / 2 + 0.05f;
    float wheelY = wheelRadius;

    // Front left wheel
    Cylinder* wheelFL = new Cylinder(wheelRadius, wheelRadius, wheelWidth, 24, m_VertexShader, m_FragmentShader);
    wheelFL->setPosition({ wheelX_front, wheelY, wheelZ });
    wheelFL->setRotation(90.0f, glm::vec3(1, 0, 0));
    wheelFL->setSideTexture("assets/textures/car/tire.jpg");
    m_Wheels.push_back(wheelFL);

    Cylinder* hubFL = new Cylinder(wheelRadius * 0.5f, wheelRadius * 0.5f, wheelWidth + 0.02f, 16, m_VertexShader, m_FragmentShader);
    hubFL->setPosition({ wheelX_front, wheelY, wheelZ + 0.01f });
    hubFL->setRotation(90.0f, glm::vec3(1, 0, 0));
    hubFL->setSideTexture("assets/textures/car/chrome.jpg");
    m_WheelHubs.push_back(hubFL);

    // Front right wheel
    Cylinder* wheelFR = new Cylinder(wheelRadius, wheelRadius, wheelWidth, 24, m_VertexShader, m_FragmentShader);
    wheelFR->setPosition({ wheelX_front, wheelY, -wheelZ });
    wheelFR->setRotation(90.0f, glm::vec3(1, 0, 0));
    wheelFR->setSideTexture("assets/textures/car/tire.jpg");
    m_Wheels.push_back(wheelFR);

    Cylinder* hubFR = new Cylinder(wheelRadius * 0.5f, wheelRadius * 0.5f, wheelWidth + 0.02f, 16, m_VertexShader, m_FragmentShader);
    hubFR->setPosition({ wheelX_front, wheelY, -wheelZ - 0.01f });
    hubFR->setRotation(90.0f, glm::vec3(1, 0, 0));
    hubFR->setSideTexture("assets/textures/car/chrome.jpg");
    m_WheelHubs.push_back(hubFR);

    // Rear left wheel
    Cylinder* wheelRL = new Cylinder(wheelRadius, wheelRadius, wheelWidth, 24, m_VertexShader, m_FragmentShader);
    wheelRL->setPosition({ wheelX_rear, wheelY, wheelZ });
    wheelRL->setRotation(90.0f, glm::vec3(1, 0, 0));
    wheelRL->setSideTexture("assets/textures/car/tire.jpg");
    m_Wheels.push_back(wheelRL);

    Cylinder* hubRL = new Cylinder(wheelRadius * 0.5f, wheelRadius * 0.5f, wheelWidth + 0.02f, 16, m_VertexShader, m_FragmentShader);
    hubRL->setPosition({ wheelX_rear, wheelY, wheelZ + 0.01f });
    hubRL->setRotation(90.0f, glm::vec3(1, 0, 0));
    hubRL->setSideTexture("assets/textures/car/chrome.jpg");
    m_WheelHubs.push_back(hubRL);

    // Rear right wheel
    Cylinder* wheelRR = new Cylinder(wheelRadius, wheelRadius, wheelWidth, 24, m_VertexShader, m_FragmentShader);
    wheelRR->setPosition({ wheelX_rear, wheelY, -wheelZ });
    wheelRR->setRotation(90.0f, glm::vec3(1, 0, 0));
    wheelRR->setSideTexture("assets/textures/car/tire_round.jpg");
    wheelRR->setBottomTexture("assets/textures/car/tire.jpg");
    wheelRR->setTopTexture("assets/textures/car/tire.jpg");
    m_Wheels.push_back(wheelRR);

    Cylinder* hubRR = new Cylinder(wheelRadius * 0.5f, wheelRadius * 0.5f, wheelWidth + 0.02f, 16, m_VertexShader, m_FragmentShader);
    hubRR->setPosition({ wheelX_rear, wheelY, -wheelZ - 0.01f });
    hubRR->setRotation(90.0f, glm::vec3(1, 0, 0));
    hubRR->setSideTexture("assets/textures/car/chrome.jpg");
    m_WheelHubs.push_back(hubRR);

    // ============================================
    // 5. HEADLIGHTS AND TAILLIGHTS
    // ============================================

    // Headlights (front)
    Cylinder* headlightL = new Cylinder(0.15f, 0.15f, 0.08f, 16, m_VertexShader, m_FragmentShader);
    headlightL->setPosition({ carLength / 2 + 0.04f, groundClearance + carHeight / 2, carWidth / 2 - 0.3f });
    headlightL->setRotation(90.0f, glm::vec3(0, 0, 1));
    headlightL->setSideTexture("assets/textures/car/headlight.jpg");
    m_Lights.push_back(headlightL);

    Cylinder* headlightR = new Cylinder(0.15f, 0.15f, 0.08f, 16, m_VertexShader, m_FragmentShader);
    headlightR->setPosition({ carLength / 2 + 0.04f, groundClearance + carHeight / 2, -carWidth / 2 + 0.3f });
    headlightR->setRotation(90.0f, glm::vec3(0, 0, 1));
    headlightR->setSideTexture("assets/textures/car/headlight.jpg");
    m_Lights.push_back(headlightR);

    // Taillights (rear) - red
    Cylinder* taillightL = new Cylinder(0.1f, 0.1f, 0.05f, 12, m_VertexShader, m_FragmentShader);
    taillightL->setPosition({ -carLength / 2 - 0.02f, groundClearance + carHeight / 2 + 0.1f, carWidth / 2 - 0.25f });
    taillightL->setRotation(90.0f, glm::vec3(0, 0, 1));
    taillightL->setSideTexture("assets/textures/car/taillight_red.jpg");
    m_Lights.push_back(taillightL);

    Cylinder* taillightR = new Cylinder(0.1f, 0.1f, 0.05f, 12, m_VertexShader, m_FragmentShader);
    taillightR->setPosition({ -carLength / 2 - 0.02f, groundClearance + carHeight / 2 + 0.1f, -carWidth / 2 + 0.25f });
    taillightR->setRotation(90.0f, glm::vec3(0, 0, 1));
    taillightR->setSideTexture("assets/textures/car/taillight_red.jpg");
    m_Lights.push_back(taillightR);

    // ============================================
    // 6. FRONT GRILLE (Chrome bars)
    // ============================================

    for (int i = 0; i < 5; i++) {
        Box* grilleBar = new Box(0.03f, 0.08f, carWidth - 0.8f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
        grilleBar->setPosition({ carLength / 2 + 0.02f, groundClearance + carHeight / 2 - 0.15f + i * 0.08f, 0.0f });
        grilleBar->setAllFacesTexture("assets/textures/car/chrome.jpg");
        m_Grille.push_back(grilleBar);
    }

    // Grille surround
    Box* grilleSurround = new Box(0.05f, 0.45f, carWidth - 0.7f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    grilleSurround->setPosition({ carLength / 2 + 0.03f, groundClearance + carHeight / 2, 0.0f });
    grilleSurround->setAllFacesTexture("assets/textures/car/chrome.jpg");
    m_Grille.push_back(grilleSurround);

    // ============================================
    // 7. BUMPERS (Chrome)
    // ============================================

    // Front bumper
    Cylinder* frontBumper = new Cylinder(0.08f, 0.08f, carWidth + 0.2f, 16, m_VertexShader, m_FragmentShader);
    frontBumper->setPosition({ carLength / 2 + 0.1f, groundClearance + 0.15f, 0.0f });
    frontBumper->setRotation(90.0f, glm::vec3(1, 0, 0));
    frontBumper->setSideTexture("assets/textures/car/chrome.jpg");
    m_Bumpers.push_back(frontBumper);

    // Rear bumper
    Cylinder* rearBumper = new Cylinder(0.08f, 0.08f, carWidth + 0.2f, 16, m_VertexShader, m_FragmentShader);
    rearBumper->setPosition({ -carLength / 2 - 0.1f, groundClearance + 0.15f, 0.0f });
    rearBumper->setRotation(90.0f, glm::vec3(1, 0, 0));
    rearBumper->setSideTexture("assets/textures/car/chrome.jpg");
    m_Bumpers.push_back(rearBumper);

    // ============================================
    // 8. SIDE MIRRORS
    // ============================================

    // Left mirror
    Box* mirrorL = new Box(0.12f, 0.08f, 0.02f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    mirrorL->setPosition({ 0.5f, groundClearance + carHeight + 0.35f, carWidth / 2 + 0.08f });
    mirrorL->setRotation(90.0f, glm::vec3(0, 1, 0));
    mirrorL->setAllFacesTexture("assets/textures/car/mirror.jpg");
    m_Mirrors.push_back(mirrorL);

    Box* mirrorArmL = new Box(0.02f, 0.02f, 0.1f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    mirrorArmL->setPosition({ 0.5f, groundClearance + carHeight + 0.35f, carWidth / 2 + 0.02f });
    mirrorArmL->setAllFacesTexture("assets/textures/car/chrome.jpg");
    m_Mirrors.push_back(mirrorArmL);

    // Right mirror
    Box* mirrorR = new Box(0.12f, 0.08f, 0.02f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    mirrorR->setPosition({ 0.5f, groundClearance + carHeight + 0.35f, -carWidth / 2 - 0.08f });
    mirrorR->setRotation(90.0f, glm::vec3(0, 1, 0));
    mirrorR->setAllFacesTexture("assets/textures/car/mirror.jpg");
    m_Mirrors.push_back(mirrorR);

    Box* mirrorArmR = new Box(0.02f, 0.02f, 0.1f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    mirrorArmR->setPosition({ 0.5f, groundClearance + carHeight + 0.35f, -carWidth / 2 - 0.02f });
    mirrorArmR->setAllFacesTexture("assets/textures/car/chrome.jpg");
    m_Mirrors.push_back(mirrorArmR);

    // ============================================
    // 9. INTERIOR - DASHBOARD
    // ============================================

    float dashY = groundClearance + carHeight + 0.25f;

    // Dashboard panel
    Box* dashboard = new Box(0.3f, 0.3f, carWidth - 0.3f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    dashboard->setPosition({ 0.55f, dashY, 0.0f });
    dashboard->setAllFacesTexture("assets/textures/car/dashboard_wood.jpg"); // Classic wood grain
    m_InteriorBoxes.push_back(dashboard);

    // Dashboard top
    Box* dashTop = new Box(0.25f, 0.05f, carWidth - 0.25f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    dashTop->setPosition({ 0.5f, dashY + 0.17f, 0.0f });
    dashTop->setAllFacesTexture("assets/textures/car/dashboard_wood.jpg");
    m_InteriorBoxes.push_back(dashTop);

    // ============================================
    // 10. INTERIOR - GAUGES (Speedometer, Tachometer, etc.)
    // ============================================

    // Main speedometer (center-left)
    Cylinder* speedometer = new Cylinder(0.1f, 0.1f, 0.02f, 16, m_VertexShader, m_FragmentShader);
    speedometer->setPosition({ 0.4f, dashY + 0.05f, 0.2f });
    speedometer->setRotation(90.0f, glm::vec3(0, 0, 1));
    speedometer->setSideTexture("assets/textures/car/gauge_speedometer.jpg");
    m_Gauges.push_back(speedometer);

    // Tachometer (center-right)
    Cylinder* tachometer = new Cylinder(0.1f, 0.1f, 0.02f, 16, m_VertexShader, m_FragmentShader);
    tachometer->setPosition({ 0.4f, dashY + 0.05f, -0.2f });
    tachometer->setRotation(90.0f, glm::vec3(0, 0, 1));
    tachometer->setSideTexture("assets/textures/car/gauge_tachometer.jpg");
    m_Gauges.push_back(tachometer);

    // Fuel gauge (small, left)
    Cylinder* fuelGauge = new Cylinder(0.06f, 0.06f, 0.02f, 12, m_VertexShader, m_FragmentShader);
    fuelGauge->setPosition({ 0.4f, dashY + 0.05f, 0.45f });
    fuelGauge->setRotation(90.0f, glm::vec3(0, 0, 1));
    fuelGauge->setSideTexture("assets/textures/car/gauge_fuel.jpg");
    m_Gauges.push_back(fuelGauge);

    // Temperature gauge (small, right)
    Cylinder* tempGauge = new Cylinder(0.06f, 0.06f, 0.02f, 12, m_VertexShader, m_FragmentShader);
    tempGauge->setPosition({ 0.4f, dashY + 0.05f, -0.45f });
    tempGauge->setRotation(90.0f, glm::vec3(0, 0, 1));
    tempGauge->setSideTexture("assets/textures/car/gauge_temp.jpg");
    m_Gauges.push_back(tempGauge);

    // ============================================
    // 11. INTERIOR - STEERING WHEEL
    // ============================================

    float steeringX = 0.35f;
    float steeringY = dashY + 0.15f;
    float steeringZ = 0.35f; // Left side (driver)

    // Steering column
    m_SteeringColumn = new Cylinder(0.03f, 0.03f, 0.25f, 12, m_VertexShader, m_FragmentShader);
    m_SteeringColumn->setPosition({ steeringX + 0.1f, steeringY - 0.1f, steeringZ });
    m_SteeringColumn->setRotation(60.0f, glm::vec3(0, 0, 1));
    m_SteeringColumn->setSideTexture("assets/textures/car/chrome.jpg");

    // Steering wheel rim (torus approximated with cylinder)
    m_SteeringWheelRim = new Cylinder(0.15f, 0.15f, 0.025f, 24, m_VertexShader, m_FragmentShader);
    m_SteeringWheelRim->setPosition({ steeringX, steeringY, steeringZ });
    m_SteeringWheelRim->setRotation(90.0f, glm::vec3(0, 0, 1));
    m_SteeringWheelRim->setSideTexture("assets/textures/car/steering_wood.jpg"); // Wood rim

    // Steering wheel spokes (3 spokes)
    for (int i = 0; i < 3; i++) {
        float angle = i * 120.0f * (M_PI / 180.0f);
        Cylinder* spoke = new Cylinder(0.015f, 0.015f, 0.12f, 8, m_VertexShader, m_FragmentShader);
        spoke->setPosition({ steeringX, steeringY, steeringZ });
        spoke->setRotation(90.0f + i * 120.0f, glm::vec3(1, 0, 0));
        spoke->setSideTexture("assets/textures/car/chrome.jpg");
        m_SteeringSpokes.push_back(spoke);
    }

    // Steering wheel center hub
    Cylinder* steeringHub = new Cylinder(0.04f, 0.04f, 0.03f, 12, m_VertexShader, m_FragmentShader);
    steeringHub->setPosition({ steeringX - 0.01f, steeringY, steeringZ });
    steeringHub->setRotation(90.0f, glm::vec3(0, 0, 1));
    steeringHub->setSideTexture("assets/textures/car/chrome.jpg");
    m_InteriorCylinders.push_back(steeringHub);

    // ============================================
    // 12. INTERIOR - SEATS
    // ============================================

    float seatY = groundClearance + carHeight + 0.15f;

    // Driver seat (left)
    // Seat base
    Box* driverSeatBase = new Box(0.45f, 0.12f, 0.4f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    driverSeatBase->setPosition({ 0.0f, seatY, 0.4f });
    driverSeatBase->setAllFacesTexture("assets/textures/car/leather_tan.jpg");
    m_Seats.push_back(driverSeatBase);

    // Seat back
    Box* driverSeatBack = new Box(0.08f, 0.4f, 0.38f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    driverSeatBack->setPosition({ -0.2f, seatY + 0.28f, 0.4f });
    driverSeatBack->setRotation(-10.0f, glm::vec3(0, 0, 1)); // Slight recline
    driverSeatBack->setAllFacesTexture("assets/textures/car/leather_tan.jpg");
    m_Seats.push_back(driverSeatBack);

    // Seat headrest
    Box* driverHeadrest = new Box(0.06f, 0.1f, 0.2f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    driverHeadrest->setPosition({ -0.15f, seatY + 0.5f, 0.4f });
    driverHeadrest->setAllFacesTexture("assets/textures/car/leather_tan.jpg");
    m_Seats.push_back(driverHeadrest);

    // Passenger seat (right)
    Box* passengerSeatBase = new Box(0.45f, 0.12f, 0.4f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    passengerSeatBase->setPosition({ 0.0f, seatY, -0.4f });
    passengerSeatBase->setAllFacesTexture("assets/textures/car/leather_tan.jpg");
    m_Seats.push_back(passengerSeatBase);

    Box* passengerSeatBack = new Box(0.08f, 0.4f, 0.38f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    passengerSeatBack->setPosition({ -0.2f, seatY + 0.28f, -0.4f });
    passengerSeatBack->setRotation(-10.0f, glm::vec3(0, 0, 1));
    passengerSeatBack->setAllFacesTexture("assets/textures/car/leather_tan.jpg");
    m_Seats.push_back(passengerSeatBack);

    Box* passengerHeadrest = new Box(0.06f, 0.1f, 0.2f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    passengerHeadrest->setPosition({ -0.15f, seatY + 0.5f, -0.4f });
    passengerHeadrest->setAllFacesTexture("assets/textures/car/leather_tan.jpg");
    m_Seats.push_back(passengerHeadrest);

    // Rear bench seat (if 4-seater)
    Box* rearSeatBase = new Box(0.5f, 0.12f, carWidth - 0.5f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    rearSeatBase->setPosition({ -0.6f, seatY, 0.0f });
    rearSeatBase->setAllFacesTexture("assets/textures/car/leather_tan.jpg");
    m_Seats.push_back(rearSeatBase);

    Box* rearSeatBack = new Box(0.08f, 0.4f, carWidth - 0.55f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    rearSeatBack->setPosition({ -0.8f, seatY + 0.25f, 0.0f });
    rearSeatBack->setRotation(-15.0f, glm::vec3(0, 0, 1));
    rearSeatBack->setAllFacesTexture("assets/textures/car/leather_tan.jpg");
    m_Seats.push_back(rearSeatBack);

    // ============================================
    // 13. INTERIOR - GEAR SHIFTER & CENTER CONSOLE
    // ============================================

    // Center console
    Box* centerConsole = new Box(0.6f, 0.15f, 0.2f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    centerConsole->setPosition({ 0.1f, seatY + 0.08f, 0.0f });
    centerConsole->setAllFacesTexture("assets/textures/car/dashboard_wood.jpg");
    m_InteriorBoxes.push_back(centerConsole);

    // Gear shifter base
    Box* shifterBase = new Box(0.08f, 0.05f, 0.08f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    shifterBase->setPosition({ 0.15f, seatY + 0.18f, 0.0f });
    shifterBase->setAllFacesTexture("assets/textures/car/chrome.jpg");
    m_InteriorBoxes.push_back(shifterBase);

    // Gear shifter stick
    Cylinder* shifterStick = new Cylinder(0.02f, 0.02f, 0.15f, 8, m_VertexShader, m_FragmentShader);
    shifterStick->setPosition({ 0.15f, seatY + 0.28f, 0.0f });
    shifterStick->setSideTexture("assets/textures/car/chrome.jpg");
    m_InteriorCylinders.push_back(shifterStick);

    // Gear shifter knob
    Cylinder* shifterKnob = new Cylinder(0.03f, 0.025f, 0.04f, 12, m_VertexShader, m_FragmentShader);
    shifterKnob->setPosition({ 0.15f, seatY + 0.37f, 0.0f });
    shifterKnob->setSideTexture("assets/textures/car/leather_black.jpg");
    m_InteriorCylinders.push_back(shifterKnob);

    // ============================================
    // 14. DOOR HANDLES
    // ============================================

    // Left door handle
    Box* handleL = new Box(0.12f, 0.025f, 0.03f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    handleL->setPosition({ 0.3f, groundClearance + carHeight / 2 + 0.25f, carWidth / 2 + 0.02f });
    handleL->setAllFacesTexture("assets/textures/car/chrome.jpg");
    m_DoorHandles.push_back(handleL);

    // Right door handle
    Box* handleR = new Box(0.12f, 0.025f, 0.03f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    handleR->setPosition({ 0.3f, groundClearance + carHeight / 2 + 0.25f, -carWidth / 2 - 0.02f });
    handleR->setAllFacesTexture("assets/textures/car/chrome.jpg");
    m_DoorHandles.push_back(handleR);

    // Rear door handles
    Box* handleRL = new Box(0.12f, 0.025f, 0.03f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    handleRL->setPosition({ -0.5f, groundClearance + carHeight / 2 + 0.25f, carWidth / 2 + 0.02f });
    handleRL->setAllFacesTexture("assets/textures/car/chrome.jpg");
    m_DoorHandles.push_back(handleRL);

    Box* handleRR = new Box(0.12f, 0.025f, 0.03f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    handleRR->setPosition({ -0.5f, groundClearance + carHeight / 2 + 0.25f, -carWidth / 2 - 0.02f });
    handleRR->setAllFacesTexture("assets/textures/car/chrome.jpg");
    m_DoorHandles.push_back(handleRR);

    // ============================================
    // 15. EXHAUST PIPES
    // ============================================

    Cylinder* exhaustL = new Cylinder(0.04f, 0.04f, 0.2f, 12, m_VertexShader, m_FragmentShader);
    exhaustL->setPosition({ -carLength / 2 - 0.1f, groundClearance + 0.1f, 0.4f });
    exhaustL->setRotation(90.0f, glm::vec3(0, 0, 1));
    exhaustL->setSideTexture("assets/textures/car/chrome.jpg");
    m_ExhaustPipes.push_back(exhaustL);

    Cylinder* exhaustR = new Cylinder(0.04f, 0.04f, 0.2f, 12, m_VertexShader, m_FragmentShader);
    exhaustR->setPosition({ -carLength / 2 - 0.1f, groundClearance + 0.1f, -0.4f });
    exhaustR->setRotation(90.0f, glm::vec3(0, 0, 1));
    exhaustR->setSideTexture("assets/textures/car/chrome.jpg");
    m_ExhaustPipes.push_back(exhaustR);

    // ============================================
    // 16. INTERIOR - REARVIEW MIRROR
    // ============================================

    Box* rearviewMirror = new Box(0.18f, 0.06f, 0.02f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    rearviewMirror->setPosition({ 0.6f, groundClearance + carHeight + cabinHeight - 0.1f, 0.0f });
    rearviewMirror->setAllFacesTexture("assets/textures/car/mirror.jpg");
    rearviewMirror->setRotation(90.0f, glm::vec3(0, 1, 0));
    m_Mirrors.push_back(rearviewMirror);

    Box* rearviewArm = new Box(0.02f, 0.08f, 0.02f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    rearviewArm->setPosition({ 0.62f, groundClearance + carHeight + cabinHeight - 0.04f, 0.0f });
    rearviewArm->setAllFacesTexture("assets/textures/car/chrome.jpg");
    m_Mirrors.push_back(rearviewArm);

    // ============================================
    // 17. FLOOR MATS
    // ============================================

    Box* floorMatDriver = new Box(0.4f, 0.01f, 0.35f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    floorMatDriver->setPosition({ 0.2f, groundClearance + carHeight + 0.01f, 0.4f });
    floorMatDriver->setAllFacesTexture("assets/textures/car/floor_mat.jpg");
    m_InteriorBoxes.push_back(floorMatDriver);

    Box* floorMatPassenger = new Box(0.4f, 0.01f, 0.35f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    floorMatPassenger->setPosition({ 0.2f, groundClearance + carHeight + 0.01f, -0.4f });
    floorMatPassenger->setAllFacesTexture("assets/textures/car/floor_mat.jpg");
    m_InteriorBoxes.push_back(floorMatPassenger);

    // ============================================
    // 18. DOOR PANELS (Interior)
    // ============================================

    // Left door panel
    Box* doorPanelL = new Box(0.9f, 0.35f, 0.03f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    doorPanelL->setPosition({ 0.2f, groundClearance + carHeight + 0.22f, carWidth / 2 - 0.08f });
    doorPanelL->setAllFacesTexture("assets/textures/car/door_panel.jpg");
    m_InteriorBoxes.push_back(doorPanelL);

    // Right door panel
    Box* doorPanelR = new Box(0.9f, 0.35f, 0.03f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    doorPanelR->setPosition({ 0.2f, groundClearance + carHeight + 0.22f, -carWidth / 2 + 0.08f });
    doorPanelR->setAllFacesTexture("assets/textures/car/door_panel.jpg");
    m_InteriorBoxes.push_back(doorPanelR);

    // Armrests on doors
    Box* armrestL = new Box(0.25f, 0.04f, 0.08f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    armrestL->setPosition({ 0.2f, groundClearance + carHeight + 0.32f, carWidth / 2 - 0.12f });
    armrestL->setAllFacesTexture("assets/textures/car/leather_tan.jpg");
    m_InteriorBoxes.push_back(armrestL);

    Box* armrestR = new Box(0.25f, 0.04f, 0.08f, m_VertexShader, m_FragmentShader, {}, glm::vec3(0));
    armrestR->setPosition({ 0.2f, groundClearance + carHeight + 0.32f, -carWidth / 2 + 0.12f });
    armrestR->setAllFacesTexture("assets/textures/car/leather_tan.jpg");
    m_InteriorBoxes.push_back(armrestR);
}


void ClassicCar::drawOpaque() {

    updateModelMatrix();
    for (auto* box : m_BodyBoxes) box->setParentModel(getModel());
    for (auto* cyl : m_BodyCylinders) cyl->setParentModel(getModel());

    // Draw wheels
    for (auto* wheel : m_Wheels) wheel->setParentModel(getModel());
    for (auto* hub : m_WheelHubs) hub->setParentModel(getModel());

    // Draw interior
    for (auto* box : m_InteriorBoxes) box->setParentModel(getModel());
    for (auto* cyl : m_InteriorCylinders) cyl->setParentModel(getModel());

    // Draw seats
    for (auto* seat : m_Seats) seat->setParentModel(getModel());

    // Draw lights
    for (auto* light : m_Lights) light->setParentModel(getModel());

    // Draw gauges
    for (auto* gauge : m_Gauges) gauge->setParentModel(getModel());

    // Draw steering wheel
    if (m_SteeringColumn) m_SteeringColumn->setParentModel(getModel());
    if (m_SteeringWheelRim) m_SteeringWheelRim->setParentModel(getModel());
    for (auto* spoke : m_SteeringSpokes) spoke->setParentModel(getModel());

    // Draw mirrors
    for (auto* mirror : m_Mirrors) mirror->setParentModel(getModel());

    // Draw grille
    for (auto* grillePart : m_Grille) grillePart->setParentModel(getModel());

    // Draw bumpers
    for (auto* bumper : m_Bumpers) bumper->setParentModel(getModel());

    // Draw door handles
    for (auto* handle : m_DoorHandles) handle->setParentModel(getModel());

    // Draw exhaust
    for (auto* pipe : m_ExhaustPipes) pipe->setParentModel(getModel());

    for (auto* box : m_BodyBoxes) box->drawOpaque();

    for (auto* cyl : m_BodyCylinders) cyl->drawOpaque();

    // Draw wheels
    for (auto* wheel : m_Wheels) wheel->drawOpaque();
    for (auto* hub : m_WheelHubs) hub->drawOpaque();

    // Draw interior
    for (auto* box : m_InteriorBoxes) box->drawOpaque();
    for (auto* cyl : m_InteriorCylinders) cyl->drawOpaque();

    // Draw seats
    for (auto* seat : m_Seats) seat->drawOpaque();

    // Draw lights
    for (auto* light : m_Lights) light->drawOpaque();

    // Draw gauges
    for (auto* gauge : m_Gauges) gauge->drawOpaque();

    // Draw steering wheel
    if (m_SteeringColumn) m_SteeringColumn->drawOpaque();
    if (m_SteeringWheelRim) m_SteeringWheelRim->drawOpaque();
    for (auto* spoke : m_SteeringSpokes) spoke->drawOpaque();

    // Draw mirrors
    for (auto* mirror : m_Mirrors) mirror->drawOpaque();

    // Draw grille
    for (auto* grillePart : m_Grille) grillePart->drawOpaque();

    // Draw bumpers
    for (auto* bumper : m_Bumpers) bumper->drawOpaque();

    // Draw door handles
    for (auto* handle : m_DoorHandles) handle->drawOpaque();

    // Draw exhaust
    for (auto* pipe : m_ExhaustPipes) pipe->drawOpaque();
}

void ClassicCar::drawTransparent() {
    // Draw windows last for proper transparency
    for (auto* window : m_Windows) window->drawTransparent();
}

void ClassicCar::getTransparent() {
    for (auto* window : m_Windows) window->getTransparent();
}