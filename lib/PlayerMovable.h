#ifndef PLAYERMOVABLE_H
#define PLAYERMOVABLE_H
#include <iostream>
#include "SDL.h"

#include "ustawienia.h"
#include "functionality/LTexture.h"
#include "rendering/Renderable.h"
#include "rendering/Moving.h"

class PlayerMovable : public Renderable, public Moving {
private:

    const std::string NAME;

public:

    PlayerMovable(rendererType&, textureType, kameraType);

    void handleEvent(SDL_Event&);

    void render();

    int width() override;
    int height() override;

    int getPosX() override;
    int getPosY() override;
};

#endif