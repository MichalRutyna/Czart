#ifndef PLAYERMOVABLE_H
#define PLAYERMOVABLE_H
#include <iostream>
#include "SDL.h"

#include "ustawienia.h"
#include "LTexture.h"
#include "Renderable.h"

class PlayerMovable : public Renderable {
private:
    const int mWIDTH;
    const int mHEIGHT;
    const std::string NAME;

    // Bardziej przyśpiesznie
    const double VELOCITY;

    // Faktyczne pozycje
    double mPosX, mPosY;
    double oldX, oldY;
    double newX, newY;

    // Aktualna prędkość
    double mVelX, mVelY;

public:
    PlayerMovable(rendererType&, kameraType, textureType);

    void handleEvent(SDL_Event&);

    void move_step(int timeStep);

    void move(double alpha);

    void render();

    double getPosX();
    double getPosY();

    int width();
    int height();
};

#endif