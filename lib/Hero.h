#ifndef HERO_H
#define HERO_H
#include <iostream>
#include "SDL.h"

#include "ustawienia.h"
#include "LTexture.h"

class Hero{
private:
    const int WIDTH;
    const int HEIGHT;
    const std::string NAME;

    // Bardziej przyśpiesznie
    const int VELOCITY;

    // Faktyczne pozycje
    int mPosX, mPosY;

    // Aktualna prędkość
    int mVelX, mVelY;

    textureType tekstura;

public:
    Hero(textureType);

    void handleEvent(SDL_Event&);

    void move();

    void render(rendererType&, int camX, int camY);

    int getPosX();
    int getPosY();

    int heroWidth();
    int heroHeight();
};

#endif