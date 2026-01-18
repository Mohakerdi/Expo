#include "Expo/InnovationSection.h"
#include "Scene.h"

InnovationSection::InnovationSection(glm::vec3 origin) : SectionBase(origin) {
    build();
}

InnovationSection::~InnovationSection() {
    cleanup();

}


void InnovationSection::build() {


 
    Box* podium = new Box(8.0f, 0.8f, 12.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));
    podium->setPosition({ m_Origin.x - 17, 0.4f, m_Origin.z });
    podium->setRotation(45, { 0, 1, 0 });
    podium->setAllFacesTexture("assets/textures/car/spot.jpg"); // Smooth floor
    m_Boxes.push_back(podium);

    Box* podium2 = new Box(8.0f, 0.8f, 12.0f,
        "assets/shaders/vertexSh.vert",
        "assets/shaders/fragSh.frag",
        {}, glm::vec3(0)
    );
    podium2->setPosition({ m_Origin.x -17 , 0.4f, m_Origin.z + 15 });
    podium2->setRotation(45, { 0, 1, 0 });
    podium2->setAllFacesTexture("assets/textures/car/spot.jpg");
    m_Boxes.push_back(podium2);


    Box* podium3 = new Box(8.0f, 0.8f, 12.0f,
        "assets/shaders/vertexSh.vert",
        "assets/shaders/fragSh.frag",
        {}, glm::vec3(0)
    );
    podium3->setPosition({ m_Origin.x - 17, 0.4f, m_Origin.z + 30 });
    podium3->setRotation(45, { 0, 1, 0 });
    podium3->setAllFacesTexture("assets/textures/car/spot.jpg");
    m_Boxes.push_back(podium3);

    // Podium 4 (خلف)
    Box* podium4 = new Box(8.0f, 0.8f, 12.0f,
        "assets/shaders/vertexSh.vert",
        "assets/shaders/fragSh.frag",
        {}, glm::vec3(0)
    );
    podium4->setPosition({ m_Origin.x - 17, 0.4f, m_Origin.z -15 });
    podium4->setRotation(45, { 0, 1, 0 });
    podium4->setAllFacesTexture("assets / textures / car / spot.jpg");
   m_Boxes.push_back(podium4);

 
    ModelObject* car = new ModelObject(
        "assets/models/creative_car/scene.gltf",
        "assets/shaders/model_loading.vert",
        "assets/shaders/model_loading.frag"
    );
    car->setPosition({ m_Origin.x - 17, 0.7f, m_Origin.z });
    car->setRotationEuler(
        -90.0f,  
        0.0f,    
        55.0f    
    );
    car->setScale(2.0f);


    ModelObject* car2 = new ModelObject(
        "assets/models/creative_car2/scene.gltf",
        "assets/shaders/model_loading.vert",
        "assets/shaders/model_loading.frag"
    );
    car2->setPosition({ m_Origin.x - 17 , 0.6f, m_Origin.z + 15 });
    car2->setRotationEuler(
        0.0f,  
        +150.0f,    
        0.0f   
    );
    car2->setScale(0.017f);



    ModelObject* car3 = new ModelObject(
        "assets/models/creative_car3/scene.gltf",
        "assets/shaders/model_loading.vert",
        "assets/shaders/model_loading.frag"
    );
    car3->setPosition({ m_Origin.x - 17 , 0.8f, m_Origin.z + 30 });
    car3->setRotationEuler(
        -90.0f, 
        0.0f,    
        -135.0f    
    );
    car3->setScale(1.3f);
    
    m_Models.push_back(car);
    m_Models.push_back(car2);
    m_Models.push_back(car3);


    m_Car = new InnovationCar();

    m_Car->setPosition({ m_Origin.x - 17, 2.0f, m_Origin.z - 15 });

    m_Car->setRotation(45.0f, glm::vec3(0, 1, 0));

    // تكبير حجم السيارة
    m_Car->setScale(1.8f);



    ModelObject* time = new ModelObject(
        "assets/models/time/scene.gltf",
        "assets/shaders/model_loading.vert",
        "assets/shaders/model_loading.frag"
    );
    time->setPosition({ m_Origin.x +1 , 0.3f, m_Origin.z - 25 });
    time->setRotationEuler(
        0.0f,  
        -90.0f,    
        0.0f     
    );
    time->setScale(0.018f);
    m_Models.push_back(time);


    m_Poster= new Box(5.0f, 3.0f, 0.05f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));


    m_Poster->setPosition({ m_Origin.x - 13, 6.0f, m_Origin.z - 29 });

   
    m_Poster->setAllFacesTexture("assets/textures/car/black2.jpg");
    m_Poster->setFaceTexture(Face::Front, "assets/textures/painting1.jpg");
    m_Poster->setScale(2.7f);
    m_Boxes.push_back(m_Poster);


    m_Poster = new Box(5.0f, 3.0f, 0.05f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));


    m_Poster->setPosition({ m_Origin.x - 24, 6.0f, m_Origin.z - 17.5f });

  
    m_Poster->setRotation(90.0f, { 0, 1, 0 }); 
    m_Poster->setAllFacesTexture("assets/textures/car/black2.jpg");
    m_Poster->setFaceTexture(Face::Front, "assets/textures/painting2.jpg");
    m_Poster->setScale(2.7f);
    m_Boxes.push_back(m_Poster);


    m_Poster = new Box(5.0f, 3.0f, 0.05f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));



    m_Poster->setPosition({ m_Origin.x - 24, 6.0f, m_Origin.z + 7.5 });



   m_Poster->setRotation(90.0f, { 0, 1, 0 }); 


 
    m_Poster->setAllFacesTexture("assets/textures/car/black2.jpg");
    m_Poster->setFaceTexture(Face::Front, "assets/textures/painting3.jpg");
    m_Poster->setScale(2.7f);
    m_Boxes.push_back(m_Poster);



    m_Poster = new Box(5.0f, 3.0f, 0.05f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", {}, glm::vec3(0));


    m_Poster->setPosition({ m_Origin.x - 24, 6.0f, m_Origin.z + 32.5 });

    m_Poster->setRotation(90.0f, { 0, 1, 0 });


 
    m_Poster->setAllFacesTexture("assets/textures/car/black2.jpg");
    m_Poster->setFaceTexture(Face::Front, "assets/textures/painting4.jpg");
    m_Poster->setScale(2.7f);
    m_Boxes.push_back(m_Poster);

    

}

void InnovationSection::drawOpaque() {
    for (auto* box : m_Boxes) box->drawOpaque();
    for (auto* cyl : m_Cylinders) cyl->drawOpaque();
    for (auto* model : m_Models) model->drawOpaque();

    if (m_Car) m_Car->drawOpaque();
  
}

void InnovationSection::drawTransparent() {
    for (auto* box : m_Boxes) box->drawTransparent();
    for (auto* cyl : m_Cylinders) cyl->drawTransparent();


    if (m_Car) m_Car->drawOpaque();

}
void InnovationSection::getTransparent() {
    for (auto* box : m_Boxes) box->getTransparent();
    for (auto* cyl : m_Cylinders) cyl->getTransparent();

    if (m_Car) m_Car->getTransparent();
}
