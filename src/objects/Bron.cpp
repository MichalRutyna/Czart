#include "../../lib/objects/Bron.h"

Bron::Bron(rendererType& renderer, textureType texture, cameraType camera, std::shared_ptr<_GameObject> owner) : DMovable(renderer, texture, camera)
{
	mName = "Miecz z drutu";
	mOwner = owner;
}

void Bron::update(int _)
{
	mVisibleX = mOwner->getX();
	mVisibleY = mOwner->getY();
}