#pragma once
#include "SectionBase.h"
#include "Expo/Car/DrivableCar.h" // <--- ADD THIS

class VelocitySection : public SectionBase {
public:
    VelocitySection(glm::vec3 origin);
    ~VelocitySection() override;

    void drawOpaque() override;
    void drawTransparent() override;

    // <--- ADD THESE OVERRIDES
    void update(GLFWwindow* window, float dt) override;
    void getTransparent() override;

private:
    void build();

    // <--- ADD DRIVABLE CAR MEMBER
    DrivableCar* m_DrivableCar;
};