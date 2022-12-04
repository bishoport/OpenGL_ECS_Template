#pragma once
#include "../config.h"
#include "../ECS/ECS.h"
#include "../Lighting/light.h"

class Scene {
public:
	Scene();
	~Scene();
	void update(float rate);
	
	
	void movePlayer(glm::vec3 dPos);
	void spinPlayer(glm::vec3 dEulers);

	Entity* mainCamera;

	std::vector<Entity*> entitiesInScene;

	std::vector<Light*> lights;

};