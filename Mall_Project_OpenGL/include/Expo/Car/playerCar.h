#pragma once
#include "Object.h"
#include "Box.h"
#include "Cylinder.h" // Added for Steering Wheel Rim
#include "Wheel.h"
#include <glm/glm.hpp>

class PlayerCar : public Object
{
public:
    PlayerCar();
    ~PlayerCar() {} // Clean up handled by Box/Cylinder destructors

    void UpdateCar(GLFWwindow* window, float dt);
    void drawOpaque() override;
    void getTransparent() override;
    void onImguiRender() override;

private:
    void setTex();

    // --- CAR BODY PARTS ---
    Box m_ChassisMain;       // Main body
    Box m_ChassisBottom;    // Undercarriage (Rockers)
    Box m_Cabin;            // Top part
    Box m_Roof;             // Roof detail
    Box m_Hood;             // Front hood detail
    Box m_DoorL;
    Box m_DoorR;

    // --- GLASS ---
    Box m_WindshieldFront;
    Box m_WindshieldRear;
    Box m_RearWindow;

    // --- LIGHTS ---
    Box m_HeadlightL;
    Box m_HeadlightR;
    Box m_TaillightL;
    Box m_TaillightR;

    // --- PERFORMANCE PARTS ---
    Box m_SpoilerWing;
    Box m_SpoilerStrutL;
    Box m_SpoilerStrutR;

    // --- STEERING WHEEL (NEW) ---
    Cylinder m_SteeringWheelRim;  // The outer ring
    Box m_SteeringWheelSpokeH;    // Horizontal spoke
    Box m_SteeringWheelSpokeV;    // Vertical spoke
    Box m_SteeringWheelHub;       // Center connection

    // --- WHEELS ---
    Wheel m_WheelFL;
    Wheel m_WheelFR;
    Wheel m_WheelBL;
    Wheel m_WheelBR;

    // --- STATE ---
    float m_Speed = 0.0f;
    float m_RotationAngle = 0.0f;
    float m_SteerAngle = 0.0f;

    bool m_DoorsOpen = false;
    float m_DoorAngle = 0.0f;

    bool m_IsDriving = false; // NEW: Tracks if player is inside car
};