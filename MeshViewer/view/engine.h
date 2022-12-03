#pragma once
#include "../config.h"
#include "../gameObjects/scene.h"
#include "loaders/shaderLoader.h"
#include "../ECS/Components.h"

class Engine {
public:
	Engine(int width, int height);
	~Engine();

	void render(Scene* scene);
	unsigned int shader;
};