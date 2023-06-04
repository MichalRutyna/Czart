#ifndef BRON
#define BRON

#include <string>

#include "../ustawienia.h"
#include "../functionality/GameObjects.h"

class Bron : public DMovable
{
private:
	std::string mName;
	std::shared_ptr<_GameObject> mOwner;

public:
	Bron(rendererType& renderer, textureType texture, cameraType camera, std::shared_ptr<_GameObject> owner);

	virtual void update(int _); // mo�e by� abstrakcyjna metoda; ka�dy dziedzicz�cy rodzaj broni mo�e mie� inne miejsce do trzymania
};

#endif