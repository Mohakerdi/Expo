
#include <Expo/world_plan.h>

WorldPlan::WorldPlan() :Object(),
buildings(),
plan1(320.0f, 0.1f, 360.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
mall(120.0f, 40.1f, 120.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
street1(10.0f, 0.1f, 200.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", { {Face::Up, {1, 25}}, }),
street2(10.0f, 0.1f, 160.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", { {Face::Up, {1, 25}}, }),
plan3(140.0f, 0.1f, 10.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", { {Face::Up, {20, 3}}, }),
plan4(10.0f, 0.1f, 70.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", { {Face::Up, {3, 10}}, }),
plan5(10.0f, 10.0f, 0.5f, 300, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag"),
plan2(140.0f, 0.1f, 180.0f, "assets/shaders/vertexSh.vert", "assets/shaders/fragSh.frag", { {Face::Up, {5, 5}}, }),
bahra("assets/obj/medieval_fountain/scene.gltf", "assets/shaders/model_loading.vert", "assets/shaders/model_loading.frag"),
tree1("assets/obj/tree_1/scene.gltf", "assets/shaders/model_loading.vert", "assets/shaders/model_loading.frag")
{
	plan1.setFaceTexture(Face::Up, "assets/textures/plan/grass.jpg");
	plan2.setFaceTexture(Face::Up, "assets/textures/plan/inner-grass.png");
	plan3.setFaceTexture(Face::Up, "assets/textures/plan/p1.jpg");
	plan4.setFaceTexture(Face::Up, "assets/textures/plan/p1.jpg");
	plan5.setTopTexture("assets/textures/plan/p1.jpg");
	street1.setFaceTexture(Face::Up, "assets/textures/plan/p13.jpg");
	street2.setFaceTexture(Face::Up, "assets/textures/plan/p13.jpg");

	//Postions
	plan1.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	plan2.setPosition(glm::vec3(0.0f, 0.01f, 0.0f));
	plan3.setPosition(glm::vec3(0.0f, 0.02f,+65.0f));
	plan4.setPosition(glm::vec3(0.0f, 0.02f,+55.0f));
	plan5.setPosition(glm::vec3(0.0f, 0.02f,+65.0f));
	bahra.setPosition(glm::vec3(-0.1f, 0.2f,+65.5f));
	tree1.setPosition(glm::vec3(-10.0f, 0.2f,+105.5f));
	mall.setPosition(glm::vec3(0.0f, 0.01f + mall.getHeight()/2, -80.0f + mall.getDepth() / 2));
	
}

void WorldPlan::drawOpaque()
{
	plan1.setParentModel(getModel());
	plan2.setParentModel(getModel());
	plan3.setParentModel(getModel());
	plan4.setParentModel(getModel());
	plan5.setParentModel(getModel());
	street1.setParentModel(getModel());
	street2.setParentModel(getModel());
	mall.setParentModel(getModel());
	buildings.setParentModel(getModel());
	bahra.setParentModel(getModel());
	tree1.setParentModel(getModel());

	plan1.drawOpaque();
	plan2.drawOpaque();
	plan3.drawOpaque();
	plan4.drawOpaque();
	plan5.drawOpaque();

	bahra.setRotation(-90, glm::vec3(1.0f, 0.0f, 0.0f));
	bahra.setScale(0.02);
	bahra.drawOpaque();
	
	tree1.setRotation(0, glm::vec3(1.0f, 0.0f, 0.0f));
	tree1.setScale(0.2);
	tree1.setPosition(glm::vec3(-20.0f, 0.2f, +105.5f));
	tree1.drawOpaque();
	tree1.setPosition(glm::vec3(-20.0f, 0.2f, +85.5f));
	tree1.drawOpaque();
	tree1.setPosition(glm::vec3(50.0f, 0.2f, +105.5f));
	tree1.drawOpaque();
	tree1.setPosition(glm::vec3(50.0f, 0.2f, +85.5f));
	tree1.drawOpaque();
	tree1.setRotation(-90, glm::vec3(0.0f, 1.0f, 0.0f));
	tree1.setPosition(glm::vec3(65.0f, 0.2f, +85.5f));
	tree1.drawOpaque();
	tree1.setPosition(glm::vec3(-65.0f, 0.2f, +85.5f));
	tree1.drawOpaque();


	street1.setPosition(glm::vec3(-75.0f, 0.04f, 0.0f));
	street1.drawOpaque();
	street1.setPosition(glm::vec3(+75.0f, 0.04f, 0.0f));
	street1.drawOpaque();

	street2.setRotation(90, glm::vec3(0, 1, 0));
	street2.setPosition(glm::vec3(0.0f, 0.02f, -95.0f));
	street2.drawOpaque();
	street2.setPosition(glm::vec3(0.0f, 0.02f, 95.0f));
	street2.drawOpaque();

	buildings.setPosition(glm::vec3(-85.0f,0,0));
	buildings.drawOpaque();
	buildings.setPosition(glm::vec3(-85.0f, 0, -120));
	buildings.drawOpaque();
	buildings.setRotation(180, glm::vec3(0, 1, 0));
	buildings.setPosition(glm::vec3(85.0f,0,120));
	buildings.drawOpaque();
	buildings.setPosition(glm::vec3(90.0f, 0, 0));
	buildings.drawOpaque();
	buildings.setRotation(360, glm::vec3(0, 1, 0));

}		  

void WorldPlan::getTransparent()
{

}

void WorldPlan::onImguiRender()
{

}
