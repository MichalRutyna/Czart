#pragma once

#include "../functionality/GameObjects.h"

class Entity : public DMovable
{
protected:
	int MAX_HP = 0;
	int MAX_MANA = 0;

	int mHp = 0, mMana = 0;

public:

	int getHp();
	int getMana();
	void attack();
	Entity(rendererType& renderer, textureType tekstura, cameraType kamera) : DMovable(renderer, tekstura, kamera) {}
};

