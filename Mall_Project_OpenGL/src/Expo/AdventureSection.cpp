#include "Expo/AdventureSection.h"
#include "Expo/Car/JeepCar.h"
#include "Expo/Teble.h"  // Include Table
#include "Expo/Resturant/Chair.h"  // Include Chair
#include "Expo/Electronic/Laptop.h" // Include Laptop
#include "Expo/Flag.h"       // Include Flag
#include "Expo/Spotlight.h"  // Include Spotlight
#include "Expo/Poster.h"  // Include Poster
#include "Scene.h"
#include <cstdlib>

std::vector<JeepCar*> m_CustomCars;
std::vector<Table*> m_Tables;      // Vector للطاولات
std::vector<Chair*> m_Chairs;      // Vector للكراسي
std::vector<Laptop*> m_Laptops;    // Vector لللابتوبات
std::vector<Flag*> m_Flags;        // Vector للرايات
std::vector<Spotlight*> m_Spotlights; // Vector لمصابيح الإضاءة
std::vector<Poster*> m_Posters;    // Vector للوحات

AdventureSection::AdventureSection(glm::vec3 origin) : SectionBase(origin) {
    build();
}

AdventureSection::~AdventureSection() {
    cleanup();
}

void AdventureSection::build() {
    // --- THEME: Off-road / Dirt ---

    // 1. Podium (Dirt/Rock Texture)
    Box* podium1 = new Box(
        8.0f, 0.5f, 12.0f,
        "assets/shaders/vertexSh.vert",
        "assets/shaders/fragSh.frag",
        {},
        glm::vec3(0)
    );
    podium1->setPosition({ m_Origin.x + 15.0f, 0.25f, m_Origin.z - 15.0f });
    podium1->setRotation(-60, { 0, 1, 0 });
    podium1->setAllFacesTexture("assets/textures/dark_gray_wood.png");
    m_Boxes.push_back(podium1);

    // 2. Podium (Dirt/Rock Texture)
    Box* podium2 = new Box(
        8.0f, 0.5f, 12.0f,
        "assets/shaders/vertexSh.vert",
        "assets/shaders/fragSh.frag",
        {},
        glm::vec3(0)
    );
    podium2->setPosition({ m_Origin.x + 15.0f, 0.25f, m_Origin.z });
    podium2->setRotation(-60, { 0, 1, 0 });
    podium2->setAllFacesTexture("assets/textures/dark_gray_wood.png");
    m_Boxes.push_back(podium2);


    // 3. Podium (Dirt/Rock Texture)
    Box* podium3 = new Box(
        8.0f, 0.5f, 12.0f,
        "assets/shaders/vertexSh.vert",
        "assets/shaders/fragSh.frag",
        {},
        glm::vec3(0)
    );
    podium3->setPosition({ m_Origin.x + 15.0f, 0.25f, m_Origin.z + 15.f });
    podium3->setRotation(-60, { 0, 1, 0 });
    podium3->setAllFacesTexture("assets/textures/dark_gray_wood.png");
    m_Boxes.push_back(podium3);

    // 4. Podium (Dirt/Rock Texture)
    Box* podium4 = new Box(
        8.0f, 0.5f, 12.0f,
        "assets/shaders/vertexSh.vert",
        "assets/shaders/fragSh.frag",
        {},
        glm::vec3(0)
    );
    podium4->setPosition({ m_Origin.x + 15.0f, 0.25f, m_Origin.z + 30.f });
    podium4->setRotation(-60, { 0, 1, 0 });
    podium4->setAllFacesTexture("assets/textures/dark_gray_wood.png");
    m_Boxes.push_back(podium4);


    // Off-road Car 1
    ModelObject* car1 = new ModelObject(
        "assets/obj/jeep_renegade_2016/scene.gltf",
        "assets/shaders/model_loading.vert",
        "assets/shaders/model_loading.frag"
    );
    car1->setPosition({ m_Origin.x + 15.0f, 0.5f, m_Origin.z + 0.0f });
    car1->setScale(3.0f);
    car1->setRotationEuler(-90, 0, -60);
    m_Models.push_back(car1);

    // Off-road Car 2
    ModelObject* car2 = new ModelObject(
        "assets/obj/1992_jeep_wrangler_yj_sahara/scene.gltf",
        "assets/shaders/model_loading.vert",
        "assets/shaders/model_loading.frag"
    );
    car2->setPosition({ m_Origin.x + 15.0f, 0.5f, m_Origin.z + 15.0f });
    car2->setScale(3.0f);
    car2->setRotationEuler(-90, 0, -60);
    m_Models.push_back(car2);

    // Off-road Car 3
    ModelObject* car3 = new ModelObject(
        "assets/obj/2017_equipped_chevrolet_colorado_z71_off_road/scene.gltf",
        "assets/shaders/model_loading.vert",
        "assets/shaders/model_loading.frag"
    );
    car3->setPosition({ m_Origin.x + 15.0f, 0.5f, m_Origin.z + 30.0f });
    car3->setScale(2.5f);
    car3->setRotationEuler(-90, 1.5, -60);
    m_Models.push_back(car3);




    //////////////////////////////
    JeepCar* jeep = new JeepCar();
    jeep->setPosition({ m_Origin.x + 15.0f, 1.25f, m_Origin.z - 15.0f });
    jeep->setRotation(-60, { 0, 1, 0 });
    m_CustomCars.push_back(jeep);
    // ////////////////////////////////////

    // --- إضافة الطاولة والكرسي واللابتوب ---

    // 1. الكرسي (Chair)
    Chair* chair = new Chair();
    chair->setPosition({ m_Origin.x + 10.0f, 1.25f, m_Origin.z + 48.0f });
    chair->setScale(0.03);
    chair->setRotation(180, { 0, 1, 0 });
    m_Chairs.push_back(chair);

    // 2. الطاولة (Table)
    Table* table = new Table();
    table->setPosition({ m_Origin.x + 10.0f, 2.00f, m_Origin.z + 45.0f });
    table->setRotation(0, { 0, 1, 0 });
    table->setScale(0.04);
    m_Tables.push_back(table);

    // 3. اللابتوب (Laptop)
    Laptop* laptop = new Laptop();
    laptop->setPosition({ m_Origin.x + 10.0f, 2.5f, m_Origin.z + 45.0f });
    laptop->setScale(2.0f);
    m_Laptops.push_back(laptop);

    // --- إضافة الجماليات (Flag & Spotlight) ---

    // 1. الراية (Flag)
    Flag* flag = new Flag();
    flag->setPosition({ m_Origin.x + 5.0f, 0.0f, m_Origin.z + 48.0f });
    flag->setRotation(-145, { 0, 1, 0 });
    flag->setScale(0.03);
    m_Flags.push_back(flag);

    // 2. مصباح الإضاءة (Spotlight)
    Spotlight* spot = new Spotlight();
    spot->setPosition({ m_Origin.x + 16.0f, 0.0f, m_Origin.z + 45.0f });
    spot->setScale(0.03);
    spot->setRotation(-150, { 0, 1, 0 });
    m_Spotlights.push_back(spot);

    // --- إضافة اللوحات (Posters) ---
   // 1. لوحة ترحيب عريضة
    Poster* ad1 = new Poster("assets/textures/ads/monaliza.jpg", 5.0f, 10.0f);
    ad1->setPosition({ m_Origin.x + 16.0f, 5.5f, m_Origin.z - 29.0f });
    ad1->setRotation(0, { 0, 1, 0 });
    m_Posters.push_back(ad1);

    Poster* ad5 = new Poster("assets/textures/ads/stars.jpg", 9.0f, 9.0f);
    ad5->setPosition({ m_Origin.x + 6.0f, 5.5f, m_Origin.z - 29.0f });
    ad5->setRotation(0, { 0, 1, 0 });
    m_Posters.push_back(ad5);
    // 2. لوحة جانبية
    Poster* ad2 = new Poster("assets/textures/ads/colors.png", 9.0f, 9.0f);
    ad2->setPosition({ m_Origin.x + 24.8f, 6.0f, m_Origin.z - 0.0f });
    ad2->setRotation(-90, { 0, 1, 0 });
    m_Posters.push_back(ad2);

    // 3. لوحة مربعة صغيرة
    Poster* ad3 = new Poster("assets/textures/ads/pinkpic.jpg", 13.0f, 9.0f);
    ad3->setPosition({ m_Origin.x + 24.8f, 6.0f, m_Origin.z - 15.0f });
    ad3->setRotation(-90, { 0, 1, 0 });
    m_Posters.push_back(ad3);

    Poster* ad4 = new Poster("assets/textures/ads/adv.png", 6.0f, 8.0f);
    ad4->setPosition({ m_Origin.x + 24.8f, 6.0f, m_Origin.z + 42.0f });
    ad4->setRotation(-90, { 0, 1, 0 });
    m_Posters.push_back(ad4);

    Poster* ad6 = new Poster("assets/textures/ads/hagoelh.png", 10.0f, 8.0f);
    ad6->setPosition({ m_Origin.x + 24.8f, 6.0f, m_Origin.z + 30.0f });
    ad6->setRotation(-90, { 0, 1, 0 });
    m_Posters.push_back(ad6);

    Poster* ad7 = new Poster("assets/textures/ads/monster.png", 10.0f, 8.0f);
    ad7->setPosition({ m_Origin.x + 24.8f, 6.0f, m_Origin.z + 15.0f });
    ad7->setRotation(-90, { 0, 1, 0 });
    m_Posters.push_back(ad7);
    // ////////////////////////////////////

    // تمت إزالة Rocks و Campsite كما طلبت
}

void AdventureSection::drawOpaque() {
    for (auto* box : m_Boxes) box->drawOpaque();
    for (auto* cyl : m_Cylinders) cyl->drawOpaque();
    for (auto* model : m_Models) model->drawOpaque();
    for (auto* jeep : m_CustomCars) jeep->drawOpaque();

    // رسم العناصر الجديدة
    for (auto* table : m_Tables) table->drawOpaque();
    for (auto* chair : m_Chairs) chair->drawOpaque();
    for (auto* laptop : m_Laptops) laptop->drawOpaque();
    for (auto* flag : m_Flags) flag->drawOpaque();
    for (auto* spot : m_Spotlights) spot->drawOpaque();

    // --- رسم اللوحات ---
    for (auto* poster : m_Posters) poster->drawOpaque();
}

void AdventureSection::drawTransparent() {
    for (auto* box : m_Boxes) box->drawTransparent();
    for (auto* cyl : m_Cylinders) cyl->drawTransparent();
    for (auto* jeep : m_CustomCars) jeep->drawTransparent();

    // رسم العناصر الشفافة الجديدة
    for (auto* table : m_Tables) table->drawTransparent();
    for (auto* chair : m_Chairs) chair->drawTransparent();
    for (auto* laptop : m_Laptops) laptop->drawTransparent();
    for (auto* flag : m_Flags) flag->drawTransparent();
    for (auto* spot : m_Spotlights) spot->drawTransparent();

    // --- رسم اللوحات الشفافة ---
    for (auto* poster : m_Posters) poster->drawTransparent();
}

void AdventureSection::getTransparent() {
    for (auto* box : m_Boxes) box->getTransparent();
    for (auto* cyl : m_Cylinders) cyl->getTransparent();

    // تجميع العناصر الشفافة الجديدة
    for (auto* table : m_Tables) table->getTransparent();
    for (auto* chair : m_Chairs) chair->getTransparent();
    for (auto* laptop : m_Laptops) laptop->getTransparent();
    for (auto* flag : m_Flags) flag->getTransparent();
    for (auto* spot : m_Spotlights) spot->getTransparent();

    // --- تجميع اللوحات ---
    for (auto* poster : m_Posters) poster->getTransparent();
}