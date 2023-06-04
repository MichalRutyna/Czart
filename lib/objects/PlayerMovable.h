#ifndef PLAYERMOVABLE_H
#define PLAYERMOVABLE_H
#include <iostream>
#include "SDL.h"

#include "../ustawienia.h"
#include "../functionality/LTexture.h"
#include "../functionality/GameObjects.h"

class PlayerMovable : public DMovable
{
public:
    PlayerMovable(rendererType&, textureType, cameraType);

    void handleEvent(SDL_Event&);

};

#endif