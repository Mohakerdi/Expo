#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "Box.h"
#include "Object.h"
#include "Cylinder.h"

class ClassicCar : public Object{
public:
    ClassicCar();
    ~ClassicCar();

    void drawOpaque();
    void drawTransparent();
    void getTransparent();

private:
    void build();
    void cleanup();


    // Car body parts (exterior)
    std::vector<Box*> m_BodyBoxes;
    std::vector<Cylinder*> m_BodyCylinders;

    // Wheels
    std::vector<Cylinder*> m_Wheels;
    std::vector<Cylinder*> m_WheelHubs;

    // Interior parts
    std::vector<Box*> m_InteriorBoxes;
    std::vector<Cylinder*> m_InteriorCylinders;

    // Windows (transparent)
    std::vector<Box*> m_Windows;

    // Headlights and taillights
    std::vector<Cylinder*> m_Lights;

    // Mirrors
    std::vector<Box*> m_Mirrors;

    // Steering wheel components
    Cylinder* m_SteeringColumn;
    Cylinder* m_SteeringWheelRim;
    std::vector<Cylinder*> m_SteeringSpokes;

    // Dashboard gauges
    std::vector<Cylinder*> m_Gauges;

    // Seats
    std::vector<Box*> m_Seats;

    // Exhaust pipes
    std::vector<Cylinder*> m_ExhaustPipes;

    // Bumpers
    std::vector<Cylinder*> m_Bumpers;

    // Door handles
    std::vector<Box*> m_DoorHandles;

    // Grille
    std::vector<Box*> m_Grille;

    // Shader paths
    const char* m_VertexShader = "assets/shaders/vertexSh.vert";
    const char* m_FragmentShader = "assets/shaders/fragSh.frag";
};