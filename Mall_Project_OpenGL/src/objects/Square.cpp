#include "Square.h"
#include "Scene.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include <set>

TextureManager textureManager;
ShaderManager shaderManager;

Square::Square(const float* vertices, float size,
    const std::string& vertexPath,
    const std::string& fragmentPath)
{
    m_VAO = std::make_unique<VAO>();
    m_VBO = std::make_unique<VBO>(vertices, size);

    VBOLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);

    m_VAO->AddBuffer(*m_VBO, layout);

    m_Shader = shaderManager.getShader(vertexPath, fragmentPath);
    m_VAO->Unbind();
}

Square::~Square() {}

void Square::setTexture(const std::string& texturePath, bool isTransparent, bool, bool)
{
    m_IsTransparent = isTransparent;
    m_Texture = textureManager.getTexture(texturePath);
}

void Square::drawOpaque()
{
    if (m_IsTransparent) return;

    updateModelMatrix();

    m_Shader->Bind();
    m_Shader->setUniformMat4f("projection", Scene::getProjection());
    m_Shader->setUniformMat4f("view", Scene::getView());
    m_Shader->setUniformMat4f("model", getModel());

    m_Texture->Bind();
    m_Shader->SetUniform1i("u_Texture", 0);
    m_Shader->SetUniform1f("alpha", 1.0f);


    m_VAO->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Square::drawTransparent()
{
    if (!m_IsTransparent) return;

    updateModelMatrix();

    m_Shader->Bind();
    m_Shader->setUniformMat4f("projection", Scene::getProjection());
    m_Shader->setUniformMat4f("view", Scene::getView());
    m_Shader->setUniformMat4f("model", getModel());
 
    m_Shader->SetUniform1f("alpha", 0.3f);

    m_Texture->Bind();
    m_VAO->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Square::getTransparent()
{
    if (m_IsTransparent)
        Scene::addTransparent(this);
}

float Square::dist()
{
    return glm::distance(
        Scene::getCameraPosition(),
        getModifiedPosition(m_Position)
    );
}

void Square::onImguiRender()
{
    ImGui::SliderFloat3("Position", &m_Position.x, -100, 100);
}
