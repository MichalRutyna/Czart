#include "../lib/Kamera.h"

static UST& ust = UST::pobierz_ustawienia();

Kamera::Kamera()
{
	// POZYCJA STARTOWA
	x = 0;
	y = 0;

    w = ust.SCREEN_WIDTH;
    h = ust.SCREEN_HEIGHT;

	following = nullptr;
}

void Kamera::setFollow(std::shared_ptr<Renderable> follow)
{
    following = follow;
}

void Kamera::update()
{
    if (following == nullptr)
    {
        return;
    }
    x = (following->getPosX() + following->width() / 2) - ust.SCREEN_WIDTH / 2; //przesun kamere na stacha
    y = (following->getPosY() + following->height() / 2) - ust.SCREEN_HEIGHT / 2;

    if (x < 0)
    {
        x = 0;
    }
    if (y < 0)
    {
        y = 0;
    }
    if (x > ust.LEVEL_WIDTH - w)
    {
        x = ust.LEVEL_WIDTH - w;
    }
    if (y > ust.LEVEL_HEIGHT - h)
    {                          
        y = ust.LEVEL_HEIGHT - h;
    }
}

int Kamera::getX()
{
	return x;
}

int Kamera::getY()
{
	return y;
}
