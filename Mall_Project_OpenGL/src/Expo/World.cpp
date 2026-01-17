
#include "Scene.h"
World::World()
    : expo()
{
    init();
    setTex();
}

void World::init()
{
    skybox = std::make_unique<Skybox>(
        std::vector<std::string>{
        "assets/textures/skybox1/right.jpg",
            "assets/textures/skybox1/left.jpg",
            "assets/textures/skybox1/top.jpg",
            "assets/textures/skybox1/bottom.jpg",
            "assets/textures/skybox1/front.jpg",
            "assets/textures/skybox1/back.jpg"
    }
    );

    //ground.setPosition(glm::vec3(0.0f, -2.0f, 0.0f));
    
}

void World::drawOpaque()
{
    drawSkyBox();
    expo.drawOpaque();
    //ground.drawOpaque();
}
void World::update(GLFWwindow* window, float dt) {
  
    expo.update(window, dt);
}

void World::drawSkyBox()
{
    if (skybox)
        skybox->draw(Scene::getView(), Scene::getProjection());
}

void World::getTransparent()
{
    expo.getTransparent();

}

void World::onImguiRender()
{
}
void World::setTex()
{

}
