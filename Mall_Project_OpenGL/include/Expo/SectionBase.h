#pragma once
#include "Object.h"
#include "Box.h"
#include "Cylinder.h"
#include "ModelObject.h"
#include "glm/glm.hpp"
#include <vector>

class SectionBase {
public:
    SectionBase(glm::vec3 origin) : m_Origin(origin) {}
    virtual ~SectionBase() {
        cleanup();
    }

    // The interface that Expo will call
    virtual void drawOpaque() = 0;
    virtual void drawTransparent() = 0;
    virtual void getTransparent() = 0;
    virtual void update(GLFWwindow* window, float dt) {}

protected:
    glm::vec3 m_Origin; // The center of this section

    // Vectors to store the specific props for this section
    std::vector<Box*> m_Boxes;
    std::vector<Cylinder*> m_Cylinders;
    std::vector<ModelObject*> m_Models;

    // Helper to clean up memory when the section is destroyed
    void cleanup() {
        for (auto* b : m_Boxes) delete b;
        for (auto* c : m_Cylinders) delete c;
        for (auto* m : m_Models) delete m;

        m_Boxes.clear();
        m_Cylinders.clear();
        m_Models.clear();
    }
};