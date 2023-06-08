#pragma once

#include "PlayerMovable.h"
#include "Entity.h"
#include <string>
#include "../functionality/GameObjects.h"
#include <vector>

class Hero : public PlayerMovable
{
private:
	const std::string NAME = "Stachu";
	static const int CLIPS_SIZE = 8;
	std::shared_ptr<Entity> trackingObject;
	std::vector<std::shared_ptr<SDL_Rect>> clips;
	std::vector<std::shared_ptr<SDL_Rect>> attack_clips;
	int mFrame = 0;
	
public:
	Hero(rendererType&, textureType, textureType, textureType, cameraType);
	void render();
	void handleEvent(SDL_Event& e);
	int state = 0;
};
