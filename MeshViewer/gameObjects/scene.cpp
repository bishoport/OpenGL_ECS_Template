#include "scene.h"
#include "../ECS/Components.h"

#include "../view/loaders/imageLoader.h"
#include "../view/loaders/object_loader.h"

Manager manager;
Scene::Scene() {

	mainCamera = &manager.addEntity();
	mainCamera->addComponent<Transform>();
	mainCamera->getComponent<Transform>().position.x = 0;
	mainCamera->getComponent<Transform>().position.y = -2;
	mainCamera->getComponent<Transform>().position.z = 2;

	Image woodImage = util::load_from_file("textures/checker.jpg");
	std::vector<float> vertices = util::load_model_from_file("models/cube.obj", glm::mat4(1.0));

	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			Entity* entity = &manager.addEntity();
			entity->addComponent<Transform>();
			entity->getComponent<Transform>().position.x += i * 1.1f;
			entity->getComponent<Transform>().position.y += j * 1.1f;
			entity->addComponent<MeshFilter>();
			entity->getComponent<MeshFilter>().setMesh(vertices);
			entity->addComponent<MaterialComp>();
			entity->getComponent<MaterialComp>().setImage(&woodImage);
			entitiesInScene.push_back(entity);
		}
	}
	util::free_image_memory(woodImage);

	//LUCES
	LightCreateInfo lightInfo;
	lightInfo.color = glm::vec3(1, 0, 0);
	lightInfo.position = glm::vec3(1, 0, 2);
	lightInfo.strength = 4.0f;
	lights.push_back(new Light(&lightInfo));

	lightInfo.color = glm::vec3(0, 1, 0);
	lightInfo.position = glm::vec3(3, 2, 0);
	lights.push_back(new Light(&lightInfo));

	lightInfo.color = glm::vec3(0, 1, 1);
	lightInfo.position = glm::vec3(3, 0, 2);
	lights.push_back(new Light(&lightInfo));
}

Scene::~Scene() {
	entitiesInScene.clear();
	entitiesInScene.shrink_to_fit();
	delete mainCamera;

	for (Light* light : lights) {
		delete light;
	}
}

void Scene::update(float rate) {
	manager.refresh();
	manager.update();
}


void Scene::movePlayer(glm::vec3 dPos) {
	mainCamera->getComponent<Transform>().position += dPos;
}

void Scene::spinPlayer(glm::vec3 dEulers) {
	mainCamera->getComponent<Transform>().eulers += dEulers;

	if (mainCamera->getComponent<Transform>().eulers.z < 0) {
		mainCamera->getComponent<Transform>().eulers.z += 360;
	}
	else if (mainCamera->getComponent<Transform>().eulers.z > 360) {
		mainCamera->getComponent<Transform>().eulers.z -= 360;
	}

	mainCamera->getComponent<Transform>().eulers.y = std::max(std::min(mainCamera->getComponent<Transform>().eulers.y, 179.0f), 1.0f);
}