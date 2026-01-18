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
    ~PlayerCar() {} 

    void UpdateCar(GLFWwindow* window, float dt);
    void drawOpaque() override;
    void getTransparent() override;
    void onImguiRender() override;

private:
    void setTex();

    Box m_ChassisMain;       
    Box m_ChassisBottom;    
    Box m_Cabin;            
    Box m_Roof;             
    Box m_Hood;             
    Box m_DoorL;
    Box m_DoorR;

    Box m_WindshieldFront;
    Box m_WindshieldRear;
    Box m_RearWindow;

    Box m_HeadlightL;
    Box m_HeadlightR;
    Box m_TaillightL;
    Box m_TaillightR;

    Box m_SpoilerWing;
    Box m_SpoilerStrutL;
    Box m_SpoilerStrutR;

    Cylinder m_SteeringWheelRim;  
    Box m_SteeringWheelSpokeH;    
    Box m_SteeringWheelSpokeV;    
    Box m_SteeringWheelHub;      

    Wheel m_WheelFL;
    Wheel m_WheelFR;
    Wheel m_WheelBL;
    Wheel m_WheelBR;

    float m_Speed = 0.0f;
    float m_RotationAngle = 0.0f;
    float m_SteerAngle = 0.0f;

    bool m_DoorsOpen = false;
    float m_DoorAngle = 0.0f;

    bool m_IsDriving = false; // NEW: Tracks if player is inside car
};