#ifndef PLAYERMOVABLE_H
#define PLAYERMOVABLE_H
#include <iostream>
#include "SDL.h"

#include "../ustawienia.h"
#include "../functionality/LTexture.h"
#include "../functionality/GameObjects.h"
#include "Entity.h"

class PlayerMovable : public Entity, public _HandlingEvents
{
public:
    PlayerMovable(rendererType& r, textureType t_i, textureType t_r, textureType t_a, cameraType c);

    void handleEvent(SDL_Event&);
    textureType texture_idle;
    textureType texture_run;
    textureType texture_attack;
    int facing = 1;
};

#endif