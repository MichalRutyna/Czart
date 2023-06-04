#ifndef KAMERA
#define KAMERA

#include "../ustawienia.h"
#include "../functionality/GOInterfaces.h"


class Kamera {
private:
	float y, x;
	int w, h;
	std::shared_ptr<_GameObject> following; // TODO weakptr

public:
	Kamera();
	void setFollow(std::shared_ptr<_GameObject>);

	void update();

	float getX();
	float getY();
};

#endif // !KAMERA

