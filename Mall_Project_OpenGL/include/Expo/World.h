#pragma once
#include "Object.h"
#include "SkyBox.h"
#include "Expo/Expo.h"
#include "Box.h"
#include <memory>
#include <Expo/Car/playerCar.h>

class World : public Object
{
public:
    World();

    void init();
    void drawOpaque();
    void getTransparent();
    void onImguiRender();
    void setTex();
    void update(GLFWwindow* window, float dt);


private:
    std::unique_ptr<Skybox> skybox;   // ✅ مهم
    Box ground;
    Expo expo;
    void drawSkyBox();
};
