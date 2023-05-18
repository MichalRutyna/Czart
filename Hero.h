#ifndef HERO_H
#define HERO_H
#include <iostream>
#include "SDL.h"

#include "ustawienia.h"

class Hero{
private:
    const int WIDTH;
    const int HEIGHT;
    const std::string NAME;

    // Bardziej przyśpiesznie
    const int VELOCITY;

    // Faktyczne pozycje
    int memberPosX, memberPosY;

    // Aktualna prędkość
    int memberVelX, memberVelY;

public:
    Hero();

    void handleEvent(SDL_Event& e);

    void move();

    void render();
};

#endif