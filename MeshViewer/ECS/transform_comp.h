#pragma once

#include "Components.h"
#include "../config.h"

class Transform : public Component
{

public :
	glm::vec3 position, eulers;

	void update() override
	{
		//position.x += 0.001f;
	}

};
