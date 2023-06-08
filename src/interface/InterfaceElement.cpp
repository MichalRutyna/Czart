#include "../../lib/interface/InterfaceElement.h"

Orb::Orb(rendererType& r, textureType t, int posx, int posy, int resource, std::shared_ptr<Entity> tracked, cameraType c) : Animated(ust.ORB_SIZE, ust.ORB_SIZE), DGameObject(r, t, c)
{
    setX = posx;
    setY = posy;
    mVisibleX = posx;
    trackedResource = resource;
    trackingObject = tracked;
}

void Orb::render()
{
    check_levels();
    std::shared_ptr<SDL_Rect> newClip = clips[mFrame / 5];
    
    newClip->h = (int)(mTexture->height() * fill);
    newClip->y = mTexture->height() - newClip->h;

    mVisibleY = setY + mTexture->height() - newClip->h;

    DGameObject::changeClip(newClip);

    mFrame++;
    if (mFrame / 5 >= 30) mFrame = 0;
    DGameObject::render();
}

void Orb::check_levels()
{
    if (trackedResource == 1)
    {
        fill = (float)trackingObject->getHp() / (float)trackingObject->getMaxHp();
    }
    else if (trackedResource == 2)
    {
        fill = (float)trackingObject->getMana() / (float)trackingObject->getMaxMana();
    }
}
