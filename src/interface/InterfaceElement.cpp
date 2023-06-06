#include "../../lib/interface/InterfaceElement.h"

Orb::Orb(rendererType& r, textureType t, int posx, int posy, cameraType c) : Animated(ust.ORB_SIZE, ust.ORB_SIZE), DGameObject(r, t, c)
{
    mVisibleX = posx;
    mVisibleY = posy;
}

void Orb::render()
{
    DGameObject::changeClip(clips[mFrame / 5]);
    mFrame++;
    if (mFrame / 5 >= 30) mFrame = 0;
    DGameObject::render();
}
