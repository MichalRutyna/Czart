#ifndef KAMERA
#define KAMERA

#include "../ustawienia.h"
#include "Renderable.h"

typedef class Renderable Renderable;

class Kamera {
private:
	int y, x;
	int w, h;
	std::shared_ptr<Renderable> following;

public:
	Kamera();
	void setFollow(std::shared_ptr<Renderable>);

	void update();

	int getX();
	int getY();
};

#endif // !KAMERA

