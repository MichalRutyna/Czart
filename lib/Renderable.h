#ifndef RENDERABLE
#define RENDERABLE

#include "ustawienia.h"
#include "Kamera.h"

class Renderable
{
protected:
	kameraType kamera;
	rendererType renderer;
	textureType mTexture;

public:
	Renderable(rendererType&, kameraType, textureType);

	virtual void render(int posX, int posY); // Pozycje absolutne, kamera odejmowana w funkcji
};

#endif // !RENDERABLE
