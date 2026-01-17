#pragma once
#include "Object.h"
#include "Box.h"
#include <glm/glm.hpp>
#include <string>

class MovingDoor : public Object
{
public:
    MovingDoor(glm::vec3 position, float width, float height, float depth,
        const std::string& vertexShader, const std::string& fragmentShader);

    void update() ;

    void drawOpaque() override;
    void getTransparent() override;

    void setAllTextures(const std::string& texturePath, bool isTransparent = false);

private:
    Box m_LeftLeaf;
    Box m_RightLeaf;

    float m_SlideFactor = 0.0f;
    bool m_IsTargetOpen = false;
    float m_AnimationSpeed = 4.0f;
    float m_TriggerDistance = 8.0f;

    float m_TotalWidth;
    float m_LeafWidth;
};