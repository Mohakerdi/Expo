#include "MovingDoor.h"
#include "Scene.h"
#include <algorithm>
#include "Application.h"


MovingDoor::MovingDoor(glm::vec3 position, float width, float height, float depth,
    const std::string& vertexShader, const std::string& fragmentShader)
    : m_LeftLeaf(width / 2.0f, height, depth, vertexShader, fragmentShader),
      m_RightLeaf(width / 2.0f, height, depth, vertexShader, fragmentShader),
      m_TotalWidth(width)
{
    this->setPosition(position);
    
    m_LeafWidth = width / 2.0f;
}

void MovingDoor::setAllTextures(const std::string& texturePath, bool isTransparent)
{
    m_LeftLeaf.setAllFacesTexture(texturePath, isTransparent);
    m_RightLeaf.setAllFacesTexture(texturePath, isTransparent);
}

void MovingDoor::update() 
{
    float dt = Application::instancePtr->deltaTime;

    glm::vec3 camPos = Scene::getCameraPosition();
    float distance = glm::length(camPos - m_Position);

    m_IsTargetOpen = (distance < m_TriggerDistance);

    float target = m_IsTargetOpen ? 2.0f : 0.0f;

    if (m_SlideFactor < target) {
        m_SlideFactor += m_AnimationSpeed * dt;
        if (m_SlideFactor > 1.0f) m_SlideFactor = 1.0f;
    }
    else if (m_SlideFactor > target) {
        m_SlideFactor -= m_AnimationSpeed * dt;
        if (m_SlideFactor < 0.0f) m_SlideFactor = 0.0f;
    }

    float slideOffset = (m_LeafWidth * 0.5f) + (m_LeafWidth * 1.5f * m_SlideFactor);

    m_LeftLeaf.setPosition(glm::vec3(-m_TotalWidth / 4.0f - slideOffset, 0.0f, 0.0f));
    m_RightLeaf.setPosition(glm::vec3(m_TotalWidth / 4.0f + slideOffset, 0.0f, 0.0f));
}
void MovingDoor::drawOpaque()
{
    glm::mat4 root = getModel();
    m_LeftLeaf.setParentModel(root);
    m_RightLeaf.setParentModel(root);

    float slideOffset = (m_LeafWidth * 0.5f) + (m_LeafWidth * 1.5f * m_SlideFactor);
    
    m_LeftLeaf.setPosition( glm::vec3(-m_TotalWidth / 4.0f - slideOffset, 0.0f, 0.0f) );
    m_RightLeaf.setPosition( glm::vec3( m_TotalWidth / 4.0f + slideOffset, 0.0f, 0.0f) );

    m_LeftLeaf.drawOpaque();
    m_RightLeaf.drawOpaque();
}

void MovingDoor::getTransparent()
{
    glm::mat4 root = getModel();
    m_LeftLeaf.setParentModel(root);
    m_RightLeaf.setParentModel(root);

    float slideOffset = (m_LeafWidth * 0.5f) + (m_LeafWidth * 1.5f * m_SlideFactor);
    m_LeftLeaf.setPosition( glm::vec3(  -slideOffset, 0.0f, 0.0f) );
    m_RightLeaf.setPosition( glm::vec3(  slideOffset, 0.0f, 0.0f) );

    m_LeftLeaf.getTransparent();
    m_RightLeaf.getTransparent();
}