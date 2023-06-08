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
	float fill = 1.0f;
	int trackedResource = 0;

	int setX = 0, setY = 0;

public:
	Orb(rendererType& r, textureType t, int posx, int posy, int resource, std::shared_ptr<Entity> tracked, cameraType c = nullptr);

	void render();
	void check_levels();
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