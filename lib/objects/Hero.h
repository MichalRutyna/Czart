#pragma once

#include "PlayerMovable.h"
#include "Entity.h"
#include <string>

class Hero : public PlayerMovable, public Entity
{
private:
	const std::string NAME = "Stachu";

public:
	Hero(rendererType&, textureType, cameraType);
};
