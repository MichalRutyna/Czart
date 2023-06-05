#pragma once

#include "../functionality/GameObjects.h"
#include "../functionality/GameObjectHandler.h"
#include "../ustawienia.h"

class Entity : public DMovable
{
protected:
	int MAX_HP = 0;
	int MAX_MANA = 0;

	int mHp = 0, mMana = 0;

public:
	Entity(rendererType& renderer, textureType tekstura, cameraType kamera);
	virtual ~Entity();

	void update(const int dt);

	int getHp();
	int getMana();
	Entity(rendererType& renderer, textureType tekstura, cameraType kamera) : DMovable(renderer, tekstura, kamera) {}

	void takeDamage(int amount);
	void manaCost(int amount);

};

