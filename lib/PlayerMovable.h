#ifndef PLAYERMOVABLE_H
#define PLAYERMOVABLE_H
#include <iostream>
#include "SDL.h"

#include "ustawienia.h"
#include "functionality/LTexture.h"
#include "functionality/GameObjects.h"

class PlayerMovable : public DMovable{
private:

    const std::string NAME;

public:

    PlayerMovable(rendererType&, textureType, kameraType);

    void handleEvent(SDL_Event&);

};

#endif