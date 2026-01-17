#pragma once
#include "SectionBase.h"

class AdventureSection : public SectionBase {
public:
    AdventureSection(glm::vec3 origin);
    ~AdventureSection() override;

    void drawOpaque() override;
    void drawTransparent() override;
    void getTransparent() override;

private:
    void build();
};