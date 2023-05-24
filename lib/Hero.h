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
    const double VELOCITY;

    // Faktyczne pozycje
    double mPosX, mPosY;
    double oldX, oldY;

    // Aktualna prędkość
    double mVelX, mVelY;

    textureType tekstura;

public:
    Hero(textureType);

    void handleEvent(SDL_Event&);

    void move_step(int timeStep);

    void move(double alpha);

    void render(rendererType&, int camX, int camY);

    double getPosX();
    double getPosY();

    int width();
    int height();
};

#endif