#pragma once
#include "../config.h"
#include "../gameObjects/scene.h"
#include "loaders/shaderLoader.h"
#include "../ECS/Components.h"


struct LightLocation {
	std::array<unsigned int, 8> colorLoc, positionLoc, strengthLoc;
};

class Engine {
public:
	Engine(int width, int height);
	~Engine();

	void render(Scene* scene);
	unsigned int shader;

	LightLocation lights;
	unsigned int cameraPosLoc;
};