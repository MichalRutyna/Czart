#pragma once

#include "../functionality/GameObjects.h"
#include "../functionality/GameObjectHandler.h"
#include "../ustawienia.h"

class Entity : public DMovable
{
protected:
	int MAX_HP = 0;
	int MAX_MANA = 0;
	int ATTACK = 10;
	int KNOCKBACK = 80;

	int mHp = 0;
	int mMana = 0;


public:
	Entity(rendererType& renderer, textureType tekstura, cameraType kamera);
	virtual ~Entity();

	void update(const int dt);

	int getHp();
	int getMaxHp();
	int getMana();
	int getMaxMana();

	void takeDamage(int amount, int side);
	void manaCost(int amount);

};

