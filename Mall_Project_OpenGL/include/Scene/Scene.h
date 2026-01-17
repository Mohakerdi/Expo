#pragma once
#include "core.h"
#include "Camera.h"
#include "Object.h"
#include <vector>
#include <Expo/World.h>
#include "CameraController.h" 


class Scene
{
public:
    Scene();
    ~Scene();

    static Scene* instancePtr;

    void draw();
    void drawTransparent();

    void onCursorPositionEvent(double x, double y);
    void processDiscreteInput(int32_t key, int32_t scancode, int32_t action, int32_t mods, float deltaTime);
    void processContinuousInput(float deltaTime);
    void onImguiRender();

    static void setCameraPosition(const glm::vec3& pos);
    static void setCameraYaw(float yaw);
    static void setCameraPitch(float pitch);

    static float getCameraYaw(); 
    static float getCameraPitch();
    static glm::mat4 getView();
    static glm::mat4 getProjection();
    static glm::vec3 getCameraPosition();
    static void updateProj();
    static void addTransparent(Object* obj);
    void init();
private:
    float lastX = 0.0f;
    float lastY = 0.0f;
    bool firstMouse = true;
    bool isDriving = false;

    World world;

    static Camera camera; 
    static CameraController cameraController; 
    static glm::mat4 s_Proj;
    static std::vector<Object*> transparentObjects;
};
