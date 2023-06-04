#pragma once

#include "PlayerMovable.h"
#include "Entity.h"
#include <string>

class Hero : public PlayerMovable
{
private:
	const std::string NAME = "Stachu";

public:
	Hero(rendererType&, textureType, cameraType);
};
