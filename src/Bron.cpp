#include "../lib/Bron.h"

Bron::Bron(rendererType& renderer, textureType texture, kameraType camera, std::shared_ptr<_GameObject> owner) : DMovable(renderer, texture, camera)
{
	mName = "Miecz z drutu";
	mOwner = owner;
}

void Bron::update(int _)
{
	mVisibleX = mOwner->getX();
	mVisibleY = mOwner->getY();
}