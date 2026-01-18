 #pragma once
#include "SectionBase.h"
#include "Expo/Car/playerCar.h" 

class HeritageSection : public SectionBase {
public:
    HeritageSection(glm::vec3 origin);
    ~HeritageSection() override;

    void drawOpaque() override;
    void drawTransparent() override;
    void update(GLFWwindow* window, float dt) override;
    void getTransparent() override;



private:
    void build();

 
    PlayerCar* m_Car;
};