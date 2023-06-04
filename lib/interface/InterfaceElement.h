#pragma once

#include <SDL.h>
#include <vector>
#include "../functionality/GameObjects.h"
#include "../objects/Entity.h"

class Orb : public DGameObject
{
private:
	static const int CLIPS_SIZE = 30;
	std::shared_ptr<Entity> trackingObject;
	std::vector<std::shared_ptr<SDL_Rect>> clips((size_t)30, std::make_shared<SDL_Rect>());

	int mFrame = 0;

public:
	Orb(rendererType&, textureType, int posx, int posy, cameraType = nullptr);

	void render();
};

class OrbBorder : public DGameObject
{
public:
	OrbBorder(rendererType& r, textureType t, int posx, int posy, cameraType c = nullptr) : DGameObject(r, t, c)
	{
		mVisibleX = posx;
		mVisibleY = posy;
	}

	// inherits default render method
};