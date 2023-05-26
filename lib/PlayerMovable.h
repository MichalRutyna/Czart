#ifndef PLAYERMOVABLE_H
#define PLAYERMOVABLE_H
#include <iostream>
#include "SDL.h"

#include "ustawienia.h"
#include "LTexture.h"
#include "Renderable.h"

class PlayerMovable : public Renderable {
private:
    const std::string NAME;

    // Bardziej przyśpiesznie
    const double VELOCITY;

    // Faktyczne pozycje
    double mPosX, mPosY;
    double oldX, oldY;

    // Aktualna prędkość
    double mVelX, mVelY;

public:
    PlayerMovable(rendererType&, textureType, kameraType);

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