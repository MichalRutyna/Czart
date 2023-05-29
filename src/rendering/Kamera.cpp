#include "../../lib/rendering/Kamera.h"

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
    x = (following->getPosX() + following->width() / 2.0f) - ust.SCREEN_WIDTH / 2.0f; //przesun kamere na stacha
    y = (following->getPosY() + following->height() / 2.0f) - ust.SCREEN_HEIGHT / 2.0f;

    if (x < 0)
    {
        x = 0.0f;
    }
    if (y < 0)
    {
        y = 0.0f;
    }
    if (x > ust.LEVEL_WIDTH - w)
    {
        x = (float)ust.LEVEL_WIDTH - w;
    }
    if (y > ust.LEVEL_HEIGHT - h)
    {                          
        y = (float)ust.LEVEL_HEIGHT - h;
    }
}

float Kamera::getX()
{
	return x;
}

float Kamera::getY()
{
	return y;
}
