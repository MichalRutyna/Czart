#include "../../lib/objects/Entity.h"

Entity::Entity(rendererType& renderer, textureType tekstura, cameraType kamera) : DMovable(renderer, tekstura, kamera)
{
	ust.objectHandler->markForAddition(std::make_shared<_GameObject>(*this));
}

Entity::~Entity()
{
	std::cout << "Usunieto entity\n";
}

void Entity::update(const int dt)
{

}

int Entity::getHp()
{
	return mHp;
}

int Entity::getMana()
{
	return mMana;
}

void Entity::takeDamage(int amount)
{
	mHp -= amount;
	if (mHp <= 0)
	{
		// request to be deleted
		ust.objectHandler->markForRemoval(std::make_shared<Entity>(this));
	}
}

void Entity::manaCost(int amount)
{
	mMana -= amount;
}
