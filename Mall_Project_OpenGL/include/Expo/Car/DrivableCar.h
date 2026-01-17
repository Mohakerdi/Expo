#pragma once
#include "Object.h"
#include "Box.h"
#include "Cylinder.h"
#include "Wheel.h"
#include <glm/glm.hpp>
#include <string>

class DrivableCar : public Object
{
public:
    DrivableCar();
    ~DrivableCar() {};

    void UpdateCar(GLFWwindow* window, float dt);
    void drawOpaque() override;
    void getTransparent() override;
    void onImguiRender() override;

private:
    void setTex();

    // --- EXTERIOR BODY ---
    Box m_ChassisMain;
    Box m_ChassisBottom;
    Box m_Hood;
    Box m_Trunk;
    Box m_SpoilerWing;
    Box m_SpoilerStrutL;
    Box m_SpoilerStrutR;

    // --- INTERIOR ---
    Box m_Dashboard;
    Cylinder m_SteerRim;
    Box m_SteerSpokeH;
    Box m_SteerSpokeV;
    Box m_SteerHub;

    // --- GLASS ---
    Box m_WindshieldFront;
    Box m_WindshieldRear;
    Box m_WindowLeft;
    Box m_WindowRight;

    // --- WHEELS ---
    Wheel m_WheelFL;
    Wheel m_WheelFR;
    Wheel m_WheelBL;
    Wheel m_WheelBR;

    // --- STATE ---
    float m_Speed = 0.0f;
    float m_RotationAngle = 0.0f;   // Car body rotation
    float m_SteerAngle = 0.0f;      // Wheel/Steering rotation
    bool m_IsDriving = false;

    // --- CAMERA LOOK (COCKPIT) ---
    float m_HeadYaw = 0.0f;         // Looking left/right inside car
    float m_HeadPitch = 0.0f;       // Looking up/down inside car
};