#ifndef BRON
#define BRON

#include <string>

#include "LTexture.h"
#include "Renderable.h"
#include "ustawienia.h"

class Bron : public Renderable
{
private:
	std::string nazwa;

	LTexture mTexture;

public:
	Bron(textureType);

	virtual void render(); // mo¿e byæ abstrakcyjna metoda; ka¿dy dziedzicz¹cy rodzaj broni mo¿e mieæ inne miejsce do trzymania
};

#endif