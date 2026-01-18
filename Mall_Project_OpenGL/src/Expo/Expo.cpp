#include "Expo/Expo.h"
#include "Scene.h"

const float FLOOR_WIDTH = 100.0f;
const float FLOOR_DEPTH = 80.0f;
const float FLOOR_Y = 0.0f;
const float MEZZANINE_Y = 12.0f;

const float ROOM_WIDTH = FLOOR_WIDTH / 5.0f;

Expo::Expo() :
    m_WorldPlan(),
    m_GroundFloor(FLOOR_WIDTH, 0.5f, FLOOR_DEPTH, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0)),
    m_SecondFloor(FLOOR_WIDTH, 0.5f, FLOOR_DEPTH, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0)),
    m_Roof(FLOOR_WIDTH, 0.5f, FLOOR_DEPTH, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0)),
    gears("assets/obj/gears/scene.gltf", "assets/shaders/model_loading.vert", "assets/shaders/model_loading.frag"),
    m_InteriorDoor1(nullptr),
    m_InteriorDoor2(nullptr)
{
    m_EntranceDoor = new MovingDoor(
        glm::vec3(0.0f, 3.8f, FLOOR_DEPTH / 2.0f - 0.2f), // Center Position
        8.0f,  // Width
        8.0f,  // Height
        0.2f,  // Depth (Thickness)
        "assets/shaders/vertexSh.vert",
        "assets/shaders/fragSh.frag"
    );
    m_EntranceDoor->setAllTextures("assets/textures/glass.png", true);
    m_WorldPlan.setPosition({ 0, -0.25, 20 });
    buildStructure();
    gears.setPosition(glm::vec3(3.4f, 12.0f, 40.7f));
    buildLighting();
    

    // --- SECTION PLACEMENT ---
    const float ZONE_W = FLOOR_WIDTH / 2.0f;
    const float ZONE_D = FLOOR_DEPTH / 2.0f;

    // Ground Floor: 3 Rooms (Left, Center, Right)
    m_SectionInnovation = new InnovationSection({ -ROOM_WIDTH * 1.5f + ROOM_WIDTH / 4, 0.0f, -ZONE_D / 2.0f + 10.0f });
    m_SectionHeritage = new HeritageSection({ 0.0f, 0.0f, -ZONE_D / 2.0f + 10.0f });
    m_SectionAdventure = new AdventureSection({ ROOM_WIDTH * 1.5f - ROOM_WIDTH / 4, 0.0f, -ZONE_D / 2.0f + 10.0f });

    // Second Floor: 1 Room (The Velocity Lounge)
    m_SectionVelocity = new VelocitySection({ 0.0f, MEZZANINE_Y, 0.0f });
}

Expo::~Expo() {
    delete m_SectionInnovation;
    delete m_SectionHeritage;
    delete m_SectionAdventure;
    delete m_SectionVelocity;

    delete m_EntranceDoor;
    delete m_InteriorDoor1;
    delete m_InteriorDoor2;

    for (auto* ptr : m_StructuralColumns) delete ptr;
    for (auto* ptr : m_MezzanineRailings) delete ptr;
    for (auto* ptr : m_TrackLights) delete ptr;
    for (auto* ptr : m_GlassWalls) delete ptr;
}

void Expo::buildStructure() {
    // Floors
    m_GroundFloor.setPosition({ 0, FLOOR_Y, 0 });
    m_SecondFloor.setPosition({ 0, MEZZANINE_Y, 0 });

    m_GroundFloor.setAllFacesTexture("assets/textures/plan/concrete.jpg");
    m_SecondFloor.setAllFacesTexture("assets/textures/plan/concrete.jpg");

    // Roof
    m_Roof.setPosition({ 0, MEZZANINE_Y + 10.0f, 0 });
    m_Roof.setAllFacesTexture("assets/textures/plan/concrete.jpg");

    
    // --- EXTERIOR GLASS BOX ---
    const float GLASS_HEIGHT = 15.0f;
    const float GLASS_THICKNESS = 0.2f;
    const float halfDepth = FLOOR_DEPTH / 2.0f;
    const float halfWidth = FLOOR_WIDTH / 2.0f;

    const float doorWidth = 8.0f;
    const float remainingWidth = FLOOR_WIDTH - doorWidth;
    const float panelWidth = remainingWidth / 2.0f;
    const float doorHeight = 10.0f;
    const float doorCenterY = 2.5f;
    float doorTopY = doorCenterY + (doorHeight / 2.0f);
    float wallTopY = GLASS_HEIGHT;
    float transomHeight = wallTopY - doorTopY;
    float transomCenterY = doorTopY + (transomHeight / 2.0f);


    // Calculate center positions for the two panels
    float leftPanelCenterX = -(panelWidth / 2.0f + doorWidth / 2.0f);
    float rightPanelCenterX = (panelWidth / 2.0f + doorWidth / 2.0f);

    // Create Left Panel
    Box* glassFrontL = new Box(panelWidth, GLASS_HEIGHT, GLASS_THICKNESS, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
    glassFrontL->setPosition({ leftPanelCenterX, GLASS_HEIGHT / 2.0f, halfDepth });
    glassFrontL->setAllFacesTexture("assets/textures/glass.png", true);
    m_GlassWalls.push_back(glassFrontL);

    // Create Right Panel
    Box* glassFrontR = new Box(panelWidth, GLASS_HEIGHT, GLASS_THICKNESS, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
    glassFrontR->setPosition({ rightPanelCenterX, GLASS_HEIGHT / 2.0f, halfDepth });
    glassFrontR->setAllFacesTexture("assets/textures/glass.png", true);
    m_GlassWalls.push_back(glassFrontR);

    // Transom (Top part of door opening)
    Box* glassFrontUp = new Box(doorWidth, transomHeight, GLASS_THICKNESS, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
    glassFrontUp->setPosition({ 0.0f, transomCenterY, halfDepth });
    glassFrontUp->setAllFacesTexture("assets/textures/glass.png", true);
    m_GlassWalls.push_back(glassFrontUp);

    // 2. Back Facade (Remains solid)
    Box* glassBack = new Box(FLOOR_WIDTH, GLASS_HEIGHT, GLASS_THICKNESS, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
    glassBack->setPosition({ 0, GLASS_HEIGHT / 2.0f, -halfDepth });
    glassBack->setAllFacesTexture("assets/textures/glass.png", true);
    m_GlassWalls.push_back(glassBack);

    // 3. Left Facade
    Box* glassLeft = new Box(GLASS_THICKNESS, GLASS_HEIGHT, FLOOR_DEPTH, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
    glassLeft->setPosition({ -halfWidth, GLASS_HEIGHT / 2.0f, 0 });
    glassLeft->setAllFacesTexture("assets/textures/glass.png", true);
    m_GlassWalls.push_back(glassLeft);

    // 4. Right Facade
    Box* glassRight = new Box(GLASS_THICKNESS, GLASS_HEIGHT, FLOOR_DEPTH, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
    glassRight->setPosition({ halfWidth, GLASS_HEIGHT / 2.0f, 0 });
    glassRight->setAllFacesTexture("assets/textures/glass.png", true);
    m_GlassWalls.push_back(glassRight);

    // --- INTERIOR DIVIDERS (UPDATED FOR DOORS) ---

    // Wall Dimensions
    const float dividerTotalHeight = 12.0f;
    const float dividerY = MEZZANINE_Y / 2.0f;
    const float dividerThick = 0.2f;
    const float dividerDepth = FLOOR_DEPTH; // 80.0

    // Door Config
    const float interiorDoorWidth = 6.0f;  // Width along Z axis (since door is rotated)
    const float interiorDoorHeight = 12.0f;
    const float interiorDoorThick = 0.2f;

    // Calculate Z-axis Split (Left/Right Panels)
    float remainingDepth = dividerDepth - interiorDoorWidth;
    float panelDepth = remainingDepth / 2.0f; // Width of the glass panels on Z axis

    float panelHeight = 12.0f;

    // Z Positions for Panels
    float zPanelLeft = -(panelDepth / 2.0f + interiorDoorWidth / 2.0f);
    float zPanelRight = (panelDepth / 2.0f + interiorDoorWidth / 2.0f);

    // Y Positions for Panels
    
    Box* glass1_L = new Box(dividerThick, panelHeight, panelDepth, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
    glass1_L->setPosition({ -ROOM_WIDTH, dividerY, zPanelLeft });
    glass1_L->setAllFacesTexture("assets/textures/glass.png", true);
    m_GlassWalls.push_back(glass1_L);

    Box* glass1_R = new Box(dividerThick, panelHeight, panelDepth, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
    glass1_R->setPosition({ -ROOM_WIDTH, dividerY, zPanelRight });
    glass1_R->setAllFacesTexture("assets/textures/glass.png", true);
    m_GlassWalls.push_back(glass1_R);

    // 1.5 Moving Door (Center) - Rotated -90 to face +X (Innovation -> Heritage)
    m_InteriorDoor1 = new MovingDoor(
        glm::vec3(-ROOM_WIDTH, dividerY, 0.0f),
        interiorDoorWidth, interiorDoorHeight, interiorDoorThick,
        "assets/shaders/vertexSh.vert",
        "assets/shaders/fragSh.frag"
    );
    m_InteriorDoor1->setRotation(90.0f, glm::vec3(0, 1, 0));
    m_InteriorDoor1->setAllTextures("assets/textures/glass.png", true);

    Box* glass2_L = new Box(dividerThick, panelHeight, panelDepth, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
    glass2_L->setPosition({ ROOM_WIDTH, dividerY, zPanelLeft });
    glass2_L->setAllFacesTexture("assets/textures/glass.png", true);
    m_GlassWalls.push_back(glass2_L);

    Box* glass2_R = new Box(dividerThick, panelHeight, panelDepth, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
    glass2_R->setPosition({ ROOM_WIDTH, dividerY, zPanelRight });
    glass2_R->setAllFacesTexture("assets/textures/glass.png", true);
    m_GlassWalls.push_back(glass2_R);

    // 2.5 Moving Door (Center) - Rotated 90 to face -X (Adventure -> Heritage)
    m_InteriorDoor2 = new MovingDoor(
        glm::vec3(ROOM_WIDTH, dividerY, 0.0f),
        interiorDoorWidth, interiorDoorHeight, interiorDoorThick,
        "assets/shaders/vertexSh.vert",
        "assets/shaders/fragSh.frag"
    );
    m_InteriorDoor2->setRotation(90.0f, glm::vec3(0, 1, 0));
    m_InteriorDoor2->setAllTextures("assets/textures/glass.png", true);

    // --- COLUMNS ---
    float colH = (MEZZANINE_Y + 10.0f) - 0.5f;
    float offset = 2.0f;
    float colX = (FLOOR_WIDTH / 2.0f) - offset;
    float colZ = (FLOOR_DEPTH / 2.0f) - offset;

    std::vector<glm::vec3> colPositions = {
        {-colX, colH / 2.0f + 0.25f, -colZ}, {colX, colH / 2.0f + 0.25f, -colZ},
        {-colX, colH / 2.0f + 0.25f,  colZ}, {colX, colH / 2.0f + 0.25f,  colZ}
    };

    for (auto& pos : colPositions) {
        Cylinder* col = new Cylinder(0.8f, 0.8f, colH, 32, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag");
        col->setPosition(pos);
        col->setSideTexture("assets/textures/plan/concrete.jpg");
        col->setTopTexture("assets/textures/plan/concrete.jpg");
        col->setBottomTexture("assets/textures/plan/concrete.jpg");
        m_StructuralColumns.push_back(col);
    }

    // --- MEZZANINE RAILINGS ---
    float railY = MEZZANINE_Y + 0.5f;
    float railThick = 0.5f;
    float innerW = FLOOR_WIDTH - 2.0f;
    float innerD = FLOOR_DEPTH - 2.0f;

    Box* railF = new Box(innerW, railThick, railThick, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
    railF->setPosition({ 0, railY, innerD / 2.0f });
    railF->setAllFacesTexture("assets/textures/plan/concrete.jpg");
    m_MezzanineRailings.push_back(railF);

    Box* railB = new Box(innerW, railThick, railThick, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
    railB->setPosition({ 0, railY, -innerD / 2.0f });
    railB->setAllFacesTexture("assets/textures/plan/concrete.jpg");
    m_MezzanineRailings.push_back(railB);

    Box* railL = new Box(railThick, railThick, innerD, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
    railL->setPosition({ -innerW / 2.0f, railY, 0 });
    railL->setAllFacesTexture("assets/textures/plan/concrete.jpg");
    m_MezzanineRailings.push_back(railL);

    Box* railR = new Box(railThick, railThick, innerD, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
    railR->setPosition({ innerW / 2.0f, railY, 0 });
    railR->setAllFacesTexture("assets/textures/plan/concrete.jpg");
    m_MezzanineRailings.push_back(railR);
}
void Expo::buildLighting() {
    float lightY = MEZZANINE_Y - 1.0f;
    for (int room = -1; room <= 1; ++room) {
        float roomCenterX = room * ROOM_WIDTH + 15 * room;
        for (int strip = -1; strip <= 1; strip += 2) {
            float stripZ = strip * 15.0f;
            Box* lightStrip = new Box(ROOM_WIDTH - 6.0f, 0.2f, 1.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
            lightStrip->setPosition({ roomCenterX, lightY, stripZ });
            lightStrip->setAllFacesTexture("assets/textures/lights.jpg");
            m_TrackLights.push_back(lightStrip);

            Box* cableL = new Box(0.05f, 1.0f, 0.05f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
            cableL->setPosition({ roomCenterX - (ROOM_WIDTH / 4.0f) , 3 * lightY / 2.0f - MEZZANINE_Y / 2 + 1.1f, stripZ });
            cableL->setAllFacesTexture("assets/textures/car/dark_grey_metal.jpg");
            m_TrackLights.push_back(cableL);

            Box* cableR = new Box(0.05f, 1.0f, 0.05f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
            cableR->setPosition({ roomCenterX + (ROOM_WIDTH / 4.0f) ,  3 * lightY / 2.0f - MEZZANINE_Y / 2 + 1.1f, stripZ });
            cableR->setAllFacesTexture("assets/textures/car/dark_grey_metal.jpg");
            m_TrackLights.push_back(cableR);
        }
    }
    Box* mezzLight = new Box(10.0f, 0.5f, 10.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
    mezzLight->setPosition({ 0, MEZZANINE_Y - 0.5f, 0 });
    mezzLight->setAllFacesTexture("assets/textures/lights.jpg");
    m_TrackLights.push_back(mezzLight);
}

void Expo::drawOpaque() {
    m_WorldPlan.drawOpaque();

    m_GroundFloor.drawOpaque();
    m_SecondFloor.drawOpaque();
    m_Roof.drawOpaque();
    gears.setParentModel(getModel());
    gears.setScale(0.2);
    gears.drawOpaque();

    for (auto* col : m_StructuralColumns) col->drawOpaque();
    for (auto* light : m_TrackLights) light->drawOpaque();

    if (m_SectionInnovation) m_SectionInnovation->drawOpaque();
    if (m_SectionHeritage)   m_SectionHeritage->drawOpaque();
    if (m_SectionAdventure)   m_SectionAdventure->drawOpaque();
    if (m_SectionVelocity)    m_SectionVelocity->drawOpaque();

    if (m_EntranceDoor) m_EntranceDoor->drawOpaque();
    if (m_InteriorDoor1) m_InteriorDoor1->drawOpaque();
    if (m_InteriorDoor2) m_InteriorDoor2->drawOpaque();
}

void Expo::update(GLFWwindow* window, float dt) {
    // Update all sections, which will in turn update their cars
    if (m_SectionInnovation) m_SectionInnovation->update(window, dt);
    if (m_SectionHeritage)   m_SectionHeritage->update(window, dt);
    if (m_SectionAdventure)   m_SectionAdventure->update(window, dt);
    if (m_SectionVelocity)    m_SectionVelocity->update(window, dt);

    if (m_EntranceDoor) m_EntranceDoor->update();
    if (m_InteriorDoor1) m_InteriorDoor1->update();
    if (m_InteriorDoor2) m_InteriorDoor2->update();
}

void Expo::drawTransparent() {
    m_WorldPlan.drawTransparent();

    // Draw ALL glass (Exterior + Interior)
    for (auto* glass : m_GlassWalls) glass->drawTransparent();

    for (auto* rail : m_MezzanineRailings) rail->drawTransparent();

    if (m_SectionInnovation) m_SectionInnovation->drawTransparent();
    if (m_SectionHeritage)   m_SectionHeritage->drawTransparent();
    if (m_SectionAdventure)   m_SectionAdventure->drawTransparent();
    if (m_SectionVelocity)    m_SectionVelocity->drawTransparent();

    if (m_EntranceDoor) m_EntranceDoor->drawTransparent();
    if (m_InteriorDoor1) m_InteriorDoor1->drawTransparent();
    if (m_InteriorDoor2) m_InteriorDoor2->drawTransparent();
}

void Expo::getTransparent() {
    m_WorldPlan.getTransparent();
    for (auto* glass : m_GlassWalls) glass->getTransparent();

    if (m_EntranceDoor) m_EntranceDoor->getTransparent();
    if (m_InteriorDoor1) m_InteriorDoor1->getTransparent();
    if (m_InteriorDoor2) m_InteriorDoor2->getTransparent();
}

void Expo::onImguiRender() {}