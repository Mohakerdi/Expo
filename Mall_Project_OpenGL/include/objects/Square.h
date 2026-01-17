#pragma once
#include "core.h"
#include "Object.h"
#include "VBO.h"
#include "VAO.h"
#include "Texture.h"
#include "Shader.h"

class Square : public Object
{
public:
    Square(const float* vertices, float size,
        const std::string& vertexPath,
        const std::string& fragmentPath);
    ~Square();

    void drawOpaque() override;
    void drawTransparent() override;
    void getTransparent() override;
    void onImguiRender() override;
    float dist() override;

    void setTexture(const std::string& texturePath,
        bool isTransparent = false,
        bool mirrorX = false,
        bool mirrorY = false);

private:
    void sortRectangleVertices();

    std::unique_ptr<VAO> m_VAO;
    std::unique_ptr<VBO> m_VBO;
    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<Texture> m_Texture;

    std::vector<glm::vec3> rectVertices;
    glm::vec3 m_Normal;
    bool m_IsTransparent = false;
};
