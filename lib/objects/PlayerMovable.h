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
    PlayerMovable(rendererType& r, textureType t, cameraType c) : Entity(r, t, c) {}

    void handleEvent(SDL_Event&);

};

#endif