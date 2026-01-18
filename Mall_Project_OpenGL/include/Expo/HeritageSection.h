#pragma once

#include "SectionBase.h"
#include "Expo/Car/ClassicCar.h"
#include <Expo/Resturant/chair.h>
#include <vector>

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

    ClassicCar* m_ClassicCar;  // The star of the show!
    std::vector<Chair*> m_Chairs;
};