#pragma once
#include "SectionBase.h"

class InnovationSection : public SectionBase {
public:
    InnovationSection(glm::vec3 origin);
    ~InnovationSection() override;

    void drawOpaque() override;
    void drawTransparent() override;
    void getTransparent() override;
private:
    void build();
};