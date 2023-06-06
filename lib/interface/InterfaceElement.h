#pragma once

#include <SDL.h>
#include <vector>
#include "../functionality/GameObjects.h"
#include "../functionality/Animated.h"
#include "../objects/Entity.h"

class Orb : public Animated, public DGameObject
{
private:
	std::shared_ptr<Entity> trackingObject;

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