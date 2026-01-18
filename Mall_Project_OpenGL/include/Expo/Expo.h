#pragma once

#include "Object.h"
#include "Box.h"
#include "Cylinder.h" 
#include "ModelObject.h"
#include "world_plan.h"
#include "Expo/Car/playerCar.h"
#include "SectionBase.h"
#include "InnovationSection.h"
#include "HeritageSection.h"
#include "AdventureSection.h"
#include "VelocitySection.h"
#include "MovingDoor.h"

#include <vector>
#include <glm/glm.hpp>

class Expo : public Object
{
public:
    Expo();
    ~Expo();

    void drawOpaque() override;
    void drawTransparent() override;
    void getTransparent() override;
    void onImguiRender() override;
    void update(GLFWwindow* window, float dt);

private:
    void buildStructure();
    void buildLighting();

    // --- ENVIRONMENT ---
    WorldPlan m_WorldPlan;

    // --- BUILDING STRUCTURE ---
    Box m_GroundFloor;
    Box m_SecondFloor;
    Box m_Roof;
    ModelObject gears;

    std::vector<Box*> m_GlassWalls; 

    std::vector<Cylinder*> m_StructuralColumns;
    std::vector<Box*> m_MezzanineRailings;

    // --- EXPO ELEMENTS ---
    std::vector<Box*> m_TrackLights;

    // --- THE 4 SECTIONS ---
    InnovationSection* m_SectionInnovation;
    HeritageSection* m_SectionHeritage;
    AdventureSection* m_SectionAdventure;
    VelocitySection* m_SectionVelocity;

    // --- DOORS ---
    MovingDoor* m_EntranceDoor; 
    MovingDoor* m_InteriorDoor1; 
    MovingDoor* m_InteriorDoor2;
};