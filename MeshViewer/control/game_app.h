#pragma once
#include "../config.h"
#include "../gameObjects/scene.h"
#include "../view/engine.h"

struct GameAppCreateInfo {
	int width;
	int height;
};

enum class returnCode {
	CONTINUE, QUIT
};

class GameApp {
public:
	GameApp(GameAppCreateInfo* createInfo);
	returnCode mainLoop();
	~GameApp();
private:
	GLFWwindow* makeWindow();
	returnCode processInput();
	void calculateFrameRate();

	GLFWwindow* window;
	int width, height;
	Scene* scene;
	Engine* renderer;

	double lastTime, currentTime;
	int numFrames;
	float frameTime;
};