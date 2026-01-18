#include "Expo/Car/InnovationCar.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <cmath>

InnovationCar::InnovationCar()
// Dimensions: Width(x), Height(y), Depth(z)
// Initialize all parts with default sizes, we position them in drawOpaque
    : m_ChassisMain(1.7f, 0.32f, 4.6f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),     // Main Red Body
    m_ChassisBottom(1.9f, 0.18f, 4.2f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),  // Black Underbody
    m_Cabin(1.7f, 0.45f, 2.4f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),           // Roof Area
    m_Roof(1.75f, 0.07f, 2.2f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),           // Roof Detail

    m_Hood(1.6f, 0.08f, 1.6f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),             // Front Hood Scoop

    m_DoorL(0.1f, 0.5f, 1.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_DoorR(0.1f, 0.5f, 1.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),

    m_WindshieldFront(1.5f, 0.6f, 0.1f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_WindshieldRear(1.5f, 0.5f, 0.1f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_RearWindow(1.5f, 0.4f, 0.1f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),

    m_HeadlightL(1.2f, 0.08f, 0.1f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_HeadlightR(1.2f, 0.08f, 0.1f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_TaillightL(0.4f, 0.1f, 0.1f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_TaillightR(0.4f, 0.1f, 0.1f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),

    m_SpoilerWing(1.4f, 0.03f, 0.25f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_SpoilerStrutL(0.1f, 0.3f, 0.1f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_SpoilerStrutR(0.1f, 0.3f, 0.1f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),

    // --- NEW: Steering Wheel Parts ---
    // Rim (Cylinder), Horizontal Spoke (Box), Vertical Spoke (Box), Center Hub (Box)
    m_SteeringWheelRim(0.35f, 0.35f, 0.04f, 20, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_SteeringWheelSpokeH(0.7f, 0.04f, 0.04f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_SteeringWheelSpokeV(0.04f, 0.7f, 0.04f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_SteeringWheelHub(0.12f, 0.12f, 0.12f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_HoverFL(0.2f, 0.2f, 0.4f, 20, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_HoverFR(0.2f, 0.2f, 0.4f, 20, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_HoverBL(0.2f, 0.2f, 0.4f, 20, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_HoverBR(0.2f, 0.2f, 0.4f, 20, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    m_WingL(4.0f, 0.1f, 1.5f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"), // جناح أيسر (عريض وطويل)
    m_WingR(4.0f, 0.1f, 1.5f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"), // جناح أيمن
    m_IsDriving(false) // Initialize state
{
    this->setPosition(glm::vec3(0.0f, 0.5f, 0.0f)); // Lift car up slightly
    setTex();
}

void InnovationCar::setTex() {
    // NOTE: Make sure these textures exist in your assets folder!

    // 1. Paint Job (Red/Blue sports car)
    std::string paint = "assets/textures/car/dark_grey_metal.jpg";

    m_ChassisMain.setAllFacesTexture(paint);
    m_Hood.setAllFacesTexture(paint);
    m_Cabin.setAllFacesTexture("assets/textures/glass.png");
    m_Roof.setAllFacesTexture(paint);

    // 2. Underbody (Black)
    m_ChassisBottom.setAllFacesTexture("assets/textures/car/dark2.jpg");
    m_SpoilerStrutL.setAllFacesTexture("assets/textures/car/dark2.jpg");
    m_SpoilerStrutR.setAllFacesTexture("assets/textures/car/dark2.jpg");

    // 3. Glass
    m_WindshieldFront.setAllFacesTexture("assets/textures/glass.png", true);
    m_WindshieldRear.setAllFacesTexture("assets/textures/glass.png", true);
    m_RearWindow.setAllFacesTexture("assets/textures/glass.png", true);

    // 4. Doors (Paint)
    m_DoorL.setAllFacesTexture(paint);
    m_DoorR.setAllFacesTexture(paint);

    // 5. Lights
    m_HeadlightL.setAllFacesTexture("assets/textures/plan/p10.jpg");
    m_HeadlightR.setAllFacesTexture("assets/textures/plan/p10.jpg");
    m_TaillightL.setAllFacesTexture("assets/textures/plan/p11.jpg");
    m_TaillightR.setAllFacesTexture("assets/textures/plan/p11.jpg");

    // 6. Spoiler
    m_SpoilerWing.setAllFacesTexture(paint);

    std::string thruster = "assets/textures/car/fire.jpg";
    m_HoverFL.setSideTexture(thruster);
    m_HoverFR.setSideTexture(thruster);
    m_HoverBL.setSideTexture(thruster);
    m_HoverBR.setSideTexture(thruster);

    
    m_WingL.setAllFacesTexture("assets/textures/car/dark2.jpg");
    m_WingR.setAllFacesTexture("assets/textures/car/dark2.jpg");

    // --- NEW: Steering Wheel Textures (Dark Plastic/Leather) ---
    std::string blackPlastic = "assets/textures/car/dark_grey_metal.jpg"; // or find a leather texture
    m_SteeringWheelRim.setSideTexture(blackPlastic);
    m_SteeringWheelRim.setTopTexture(blackPlastic);
    m_SteeringWheelRim.setBottomTexture(blackPlastic);
    m_SteeringWheelSpokeH.setAllFacesTexture(blackPlastic);
    m_SteeringWheelSpokeV.setAllFacesTexture(blackPlastic);
    m_SteeringWheelHub.setAllFacesTexture(blackPlastic);


}

void InnovationCar::UpdateCar(GLFWwindow* window, float dt) {
    // --- NEW: Enter/Exit Vehicle Logic ---
    static bool ePressed = false;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && !ePressed) {
        m_IsDriving = !m_IsDriving;
        ePressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE) {
        ePressed = false;
    }

    // Only update physics/inputs if we are driving
    if (m_IsDriving) {
        // 1. Acceleration / Braking
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) m_Speed += 30.0f * dt;
        else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) m_Speed -= 25.0f * dt;
        else m_Speed *= 0.96f; // Friction

        // 2. Steering & Direction
        if (std::abs(m_Speed) > 0.1f) {
            if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
                m_RotationAngle += 120.0f * dt;
                m_SteerAngle = 35.0f;
            }
            else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                m_RotationAngle -= 120.0f * dt;
                m_SteerAngle = -35.0f;
            }
            else m_SteerAngle = 0.0f;

            float rad = glm::radians(m_RotationAngle);

            // FIX: Access m_Position directly
            m_Position.x += std::sin(rad) * m_Speed * dt;
            m_Position.z += std::cos(rad) * m_Speed * dt;
        }
        else {
            m_SteerAngle = 0.0f;
        }
    }
    else {
        // Optional: Car slows down if you exit
        m_Speed *= 0.95f;
        if (std::abs(m_Speed) > 0.01f) {
            float rad = glm::radians(m_RotationAngle);
            m_Position.x += std::sin(rad) * m_Speed * dt;
            m_Position.z += std::cos(rad) * m_Speed * dt;
        }
        // Center steering wheel when not driving
        m_SteerAngle = 0.0f;
    }

    // FIX: Explicitly rotate the car root model to fix "static rotation" issue
    // Assuming PlayerCar inherits from a base class with setRotation(angle, axis)
    setRotation(m_RotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));

    updateModelMatrix();
}

void InnovationCar::drawOpaque() {
    glm::mat4 root = getModel();

    // --- 1. CHASSIS ---

    // Bottom undercarriage (Rocker panels) - gives it a "low" look
    m_ChassisBottom.setParentModel(root);
    m_ChassisBottom.setPosition({ 0, 0.2f, 0 });
    m_ChassisBottom.drawOpaque();

    // Main Body
    m_ChassisMain.setParentModel(root);
    m_ChassisMain.setPosition({ 0, 0.45f, -0.2f }); // Slightly back
    m_ChassisMain.drawOpaque();

    // Hood Scoop (Front detail)
    m_Hood.setParentModel(root);
    m_Hood.setPosition({ 0, 0.66f, 1.3f });
    m_Hood.drawOpaque();

    // --- 2. CABIN ---

    // The main "Greenhouse"
    m_Cabin.setParentModel(root);
    m_Cabin.setPosition({ 0, 0.9f, -0.15f });
    m_Cabin.drawOpaque();

    // Roof top
    m_Roof.setParentModel(root);
    m_Roof.setPosition({ 0, 1.15f, -0.25f });
    m_Roof.drawOpaque();

    // --- 3. LIGHTS ---

    // Headlights (Front)
    m_HeadlightL.setParentModel(root);
    m_HeadlightL.setPosition({ 0.0f, 0.48f, 2.1f });
    m_HeadlightL.drawOpaque();

    m_HeadlightR.setParentModel(root);
    m_HeadlightR.setPosition({ 0.0f, 0.48f, 2.1f });
    m_HeadlightR.drawOpaque();

    // Taillights (Rear)
    m_TaillightL.setParentModel(root);
    m_TaillightL.setPosition({ -0.6f, 0.55f, -2.3f });
    m_TaillightL.drawOpaque();

    m_TaillightR.setParentModel(root);
    m_TaillightR.setPosition({ 0.6f, 0.55f, -2.3f });
    m_TaillightR.drawOpaque();

    // --- 4. SPOILER ---

    m_SpoilerWing.setParentModel(root);
    m_SpoilerWing.setPosition({ 0, 0.75f, -2.2f });
    m_SpoilerWing.setRotation(0.0f, { 1,0,0 }); // Slight angle down
    m_SpoilerWing.drawOpaque();

    m_SpoilerStrutL.setParentModel(root);
    m_SpoilerStrutL.setPosition({ -0.6f, 0.8f, -2.0f });
    m_SpoilerStrutL.drawOpaque();

    m_SpoilerStrutR.setParentModel(root);
    m_SpoilerStrutR.setPosition({ 0.6f, 0.8f, -2.0f });
    m_SpoilerStrutR.drawOpaque();

    // --- 5. DOORS ---

    // Left Door
    m_DoorL.setParentModel(root);
    m_DoorL.setPosition({ -0.9f, 0.7f, 0.0f });
    m_DoorL.setRotation(m_DoorAngle, { 0, 1, 0 });
    m_DoorL.drawOpaque();

    // Right Door
    m_DoorR.setParentModel(root);
    m_DoorR.setPosition({ 0.9f, 0.7f, 0.0f });
    m_DoorR.setRotation(-m_DoorAngle, { 0, 1, 0 });
    m_DoorR.drawOpaque();

    // --- 6. STEERING WHEEL (NEW) ---
    // Construct a transformation matrix for the steering wheel group
    // 1. Translate to position inside the cabin
    // 2. Rotate around Z for steering (m_SteerAngle)
    // 3. Rotate around X by 90 deg to lie flat/facing driver
    glm::mat4 wheelModel = glm::translate(root, glm::vec3(0.0f, 0.7f, 0.65f));
    wheelModel = glm::rotate(wheelModel, glm::radians(m_SteerAngle), glm::vec3(0.0f, 0.0f, 1.0f));
    wheelModel = glm::rotate(wheelModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    m_SteeringWheelRim.setParentModel(wheelModel);
    m_SteeringWheelRim.drawOpaque();

    m_SteeringWheelSpokeH.setParentModel(wheelModel);
    m_SteeringWheelSpokeH.drawOpaque();

    m_SteeringWheelSpokeV.setParentModel(wheelModel);
    m_SteeringWheelSpokeV.drawOpaque();

    m_SteeringWheelHub.setParentModel(wheelModel);
    m_SteeringWheelHub.drawOpaque();

    // --- 7. WHEELS ---
    /*
    // Front Left
    m_WheelFL.setParentModel(root);
    m_WheelFL.setPosition({ -1.0f, 0.32f, 1.45f });
    m_WheelFL.setRotation(m_SteerAngle, { 0, 1, 0 });
    m_WheelFL.drawOpaque();

    // Front Right
    m_WheelFR.setParentModel(root);
    m_WheelFR.setPosition({ 1.0f, 0.32f, 1.45f });
    m_WheelFR.setRotation(m_SteerAngle, { 0, 1, 0 });
    m_WheelFR.drawOpaque();

    // Rear Left
    m_WheelBL.setParentModel(root);
    m_WheelBL.setPosition({ -1.0f, 0.32f, -1.55f });
    m_WheelBL.drawOpaque();

    // Rear Right
    m_WheelBR.setParentModel(root);
    m_WheelBR.setPosition({ 1.0f, 0.32f, -1.55f });
    m_WheelBR.drawOpaque();
    */
    // --- HOVER THRUSTERS ---
    m_HoverFL.setParentModel(root);
    m_HoverFL.setPosition({ -0.9f, 0.15f,  1.3f });
    m_HoverFL.drawOpaque();

    m_HoverFR.setParentModel(root);
    m_HoverFR.setPosition({ 0.9f, 0.15f,  1.3f });
    m_HoverFR.drawOpaque();

    m_HoverBL.setParentModel(root);
    m_HoverBL.setPosition({ -0.9f, 0.15f, -1.3f });
    m_HoverBL.drawOpaque();

    m_HoverBR.setParentModel(root);
    m_HoverBR.setPosition({ 0.9f, 0.15f, -1.3f });
    m_HoverBR.drawOpaque();

    // --- 7. WHEELS (يمكنك إلغاء التعليق عن العجلات إذا أردتها تظهر) ---
/*
m_WheelFL.setParentModel(root);
m_WheelFL.setPosition({ -1.0f, 0.32f, 1.45f });
m_WheelFL.drawOpaque();
// ... باقي العجلات ...
*/

// --- 8. WINGS (الأجنحة) --- <--- أضف هذا الجزء الجديد

// الجناح الأيسر (ممتد لليمين بالنسبة للسيارة لأنه على الجانب الأيسر)
    m_WingL.setParentModel(root);
    // الموقع: x سالب كبير (خارج جسم السيارة)، y مرتفع شوية عشان يكون كجناح طائرة، z في المنتصف
    m_WingL.setPosition({ -1.0f, 0.8f, 0.0f });
    m_WingL.setRotation(0.0f, { 0, 1, 0 }); // يمكن ميله قليلاً للأعلى ({-10, 0, 0}) ليبدو انسيابي
    m_WingL.drawOpaque();

    // الجناح الأيمن
    m_WingR.setParentModel(root);
    // الموقع: x موجب كبير
    m_WingR.setPosition({ 1.0f, 0.8f, 0.0f });
    m_WingR.setRotation(0.0f, { 0, 1, 0 });
    m_WingR.drawOpaque();

} // <--- نهاية دالة drawOpaque



void InnovationCar::getTransparent() {
    glm::mat4 root = getModel();

    // --- GLASS ---

    // Front Windshield (Angled Back)
    m_WindshieldFront.setParentModel(root);
    m_WindshieldFront.setPosition({ 0, 0.8f, 0.7f });
    m_WindshieldFront.setRotation(-35.0f, { 1, 0, 0 });
    m_WindshieldFront.getTransparent();

    // Rear Windshield (Angled Forward)
    m_WindshieldRear.setParentModel(root);
    m_WindshieldRear.setPosition({ 0, 0.8f, -1.3f });
    m_WindshieldRear.setRotation(25.0f, { 1, 0, 0 });
    m_WindshieldRear.getTransparent();

    // Small rear window
    m_RearWindow.setParentModel(root);
    m_RearWindow.setPosition({ 0, 1.1f, -1.0f });
    m_RearWindow.setRotation(0.0f, { 1, 0, 0 });
    m_RearWindow.getTransparent();
}

void InnovationCar::onImguiRender() {
    // ImGui::SliderFloat("Speed", &m_Speed, -50.0f, 50.0f);
}