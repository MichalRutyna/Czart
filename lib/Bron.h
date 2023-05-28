#ifndef BRON
#define BRON

#include <string>

#include "functionality/LTexture.h"
#include "rendering/Renderable.h"
#include "ustawienia.h"

class Bron : public Renderable
{
private:
	std::string nazwa;

	LTexture mTexture;

public:
	Bron(textureType);

	virtual void render(); // mo�e by� abstrakcyjna metoda; ka�dy dziedzicz�cy rodzaj broni mo�e mie� inne miejsce do trzymania
};

#endif