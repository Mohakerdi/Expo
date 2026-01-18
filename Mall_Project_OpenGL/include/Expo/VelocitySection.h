#pragma once
#include "SectionBase.h"

class VelocitySection : public SectionBase {
public:
    VelocitySection(glm::vec3 origin);
    ~VelocitySection() override;

    void drawOpaque() override;
    void drawTransparent() override;

    void update(GLFWwindow* window, float dt) override;
    void getTransparent() override;

private:
    void build();

};