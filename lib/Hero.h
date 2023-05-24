#ifndef HERO_H
#define HERO_H
#include <iostream>
#include "SDL.h"

#include "ustawienia.h"
#include "LTexture.h"

class Hero{
private:
    const int mWIDTH;
    const int mHEIGHT;
    const std::string NAME;

    // Bardziej przyśpiesznie
    const float VELOCITY;

    // Faktyczne pozycje
    float mPosX, mPosY;

    // Aktualna prędkość
    float mVelX, mVelY;

    textureType tekstura;

public:
    Hero(textureType);

    void handleEvent(SDL_Event&);

    void move(int timeStep);

    void render(rendererType&, int camX, int camY);

    float getPosX();
    float getPosY();

    int width();
    int height();
};

#endif