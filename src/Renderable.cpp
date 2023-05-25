#include "../lib/Renderable.h"

Renderable::Renderable(rendererType& renderer, kameraType kamera, textureType texture) :
	kamera(kamera), mTexture(texture) 
{
	renderer = renderer;
}

void Renderable::render(int posX, int posY)
{
	mTexture->render()
}
