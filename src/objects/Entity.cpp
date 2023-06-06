#include "../../lib/objects/Entity.h"


Entity::Entity(rendererType& renderer, textureType tekstura, cameraType kamera) : DMovable(renderer, tekstura, kamera)
{
	std::cout << "stworzono entity";
}

Entity::~Entity()
{
	std::cout << "Usunieto entity\n";
}

void Entity::update(const int dt)
{
	DMovable::update(dt);
}

int Entity::getHp()
{
	return mHp;
}

int Entity::getMaxHp()
{
	return MAX_HP;
}

int Entity::getMana()
{
	return mMana;
}

int Entity::getMaxMana()
{
	return MAX_MANA;
}

void Entity::takeDamage(int amount, int side)
{
	mHp -= amount;
	if (mHp <= 0)
	{
		// request to be deleted
		destroy = true;
	}
	if (side == 1)
	{
		mInternalX -= KNOCKBACK;
	}
	else
	{
		mInternalX += KNOCKBACK;
	}
}

void Entity::manaCost(int amount)
{
	mMana -= amount;
}
