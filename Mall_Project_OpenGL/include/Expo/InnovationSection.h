#pragma once
#include "SectionBase.h"
#include "Expo/Car/InnovationCar.h"

class InnovationSection : public SectionBase {
public:
    InnovationSection(glm::vec3 origin);
    ~InnovationSection() override;

    void drawOpaque() override;
    void drawTransparent() override;
    void getTransparent() override;
    InnovationCar* m_Car;
private:
    void build();
    Box* m_Poster = nullptr;
};