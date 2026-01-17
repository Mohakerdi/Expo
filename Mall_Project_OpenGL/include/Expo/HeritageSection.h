#pragma once
#include "SectionBase.h"
#include "Expo/Car/playerCar.h" // <--- ADD THIS INCLUDE

class HeritageSection : public SectionBase {
public:
    HeritageSection(glm::vec3 origin);
    ~HeritageSection() override;

    void drawOpaque() override;
    void drawTransparent() override;
    void update(GLFWwindow* window, float dt) override; // <--- ADD THIS
    void getTransparent() override;



private:
    void build();

    // <--- ADD MEMBER VARIABLE FOR THE NEW CAR
    PlayerCar* m_Car;
};