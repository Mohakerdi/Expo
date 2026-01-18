#include <Expo/Resturant/chair.h>


Chair::Chair() : 
    seat(80.0f , 20.0f , 80.0f , "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
    back(8.0f , 120.0f , 78.0f , "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag")
{
    rjls.resize(4);
    for (int i = 0; i < 4; i++)
    {
        rjls[i] = Box(20.0f, 60.0f, 20.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag");
    }
    setTex();
}

void Chair::drawOpaque() {
    glm::vec3 positions[4] = {
    glm::vec3(30.0f , -seat.getHeight() / 2 - rjls[0].getHeight() / 2 , 30.0f),
    glm::vec3(30.0f , -seat.getHeight() / 2 - rjls[0].getHeight() / 2, -30.0f),
    glm::vec3(-30.0f , -seat.getHeight() / 2 - rjls[0].getHeight() / 2 , 30.0f),
    glm::vec3(-30.0f , -seat.getHeight() / 2 - rjls[0].getHeight() / 2 , -30.0f)
    };
    updateModelMatrix();
    for (int i = 0; i < 4; i++)
    rjls[i].setParentModel(getModel());
    seat.setParentModel(getModel());
    back.setParentModel(getModel());

    for (int i = 0; i < 4; i++) {
    rjls[i].setPosition(positions[i]);
    rjls[i].drawOpaque();

    }
    seat.setPosition(glm::vec3(0.0f , 0.0f , 0.0f));
    seat.drawOpaque();
    back.setPosition(glm::vec3(35.0f , 60.0f , 0.0f));
    back.drawOpaque();
}

void Chair::getTransparent()
{
    
}

void Chair::onImguiRender()
{
    
}

void Chair::setTex()
{

    for (int i = 0; i < 4; i++)
    {

    rjls[i].setFaceTexture(Face::Up , "assets/textures/chair2.png");
    rjls[i].setFaceTexture(Face::Down , "assets/textures/chair2.png");
    rjls[i].setFaceTexture(Face::Left , "assets/textures/chair2.png");
    rjls[i].setFaceTexture(Face::Right , "assets/textures/chair2.png");
    rjls[i].setFaceTexture(Face::Back ,  "assets/textures/chair2.png");
    rjls[i].setFaceTexture(Face::Front , "assets/textures/chair2.png");
    }


    seat.setFaceTexture(Face::Up , "assets/textures/chair1.png");
    seat.setFaceTexture(Face::Down, "assets/textures/chair1.png");
    seat.setFaceTexture(Face::Left, "assets/textures/chair1.png");
    seat.setFaceTexture(Face::Right, "assets/textures/chair1.png");
    seat.setFaceTexture(Face::Back, "assets/textures/chair1.png");
    seat.setFaceTexture(Face::Front, "assets/textures/chair1.png");
    back.setFaceTexture(Face::Up , "assets/textures/chair3.png");
    back.setFaceTexture(Face::Down, "assets/textures/chair3.png");
    back.setFaceTexture(Face::Left, "assets/textures/chair3.png");
    back.setFaceTexture(Face::Right, "assets/textures/chair3.png");
    back.setFaceTexture(Face::Back, "assets/textures/chair3.png");
    back.setFaceTexture(Face::Front, "assets/textures/chair3.png");
}
