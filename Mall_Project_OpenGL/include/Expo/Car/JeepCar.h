#pragma once
#include "Object.h"
#include "Box.h"
#include "Cylinder.h"
#include <glm/glm.hpp>
#include <vector>

class JeepCar {
public:
    JeepCar();

    void setPosition(const glm::vec3& pos);
    void setRotation(float angle, const glm::vec3& axis);
    void setScale(float s);
    void setTextures();

    void update(float dt);
    void drawOpaque();
    void drawTransparent();

private:
    glm::vec3 m_Position = { 0,0,0 };
    float m_RotationAngle = 0.0f;
    glm::vec3 m_RotationAxis = { 0,1,0 };
    float m_Scale = 1.0f;

    glm::mat4 getModelMatrix();

    // --- Jeep Body Parts ---
    Box m_BodyMain;        // Main chassis
    Box m_BodyFront;       // Front hood (bonnet)
    Box m_BodyRear;        // Rear cargo area
    Box m_BodyRoof;        // Roof

    // Bumpers (New for Professional Look)
    Box m_BumperFront;
    Box m_BumperRear;

    // Windows
    Box m_Windshield;
    Box m_SideWindowL;
    Box m_SideWindowR;
    Box m_RearWindow;

    // Lights
    Box m_HeadlightL;
    Box m_HeadlightR;
    Box m_TaillightL;      // New
    Box m_TaillightR;      // New

    // Grill
    Box m_Grill;

    // Wheels (Tires)
    Cylinder m_WheelFL;
    Cylinder m_WheelFR;
    Cylinder m_WheelBL;
    Cylinder m_WheelBR;

    // Rims (Chrome inner wheels - New)
    Cylinder m_RimFL;
    Cylinder m_RimFR;
    Cylinder m_RimBL;
    Cylinder m_RimBR;

    // Spare Tire
    Cylinder m_SpareTire;
    Cylinder m_SpareTireRim; // Rim for the spare tire
};