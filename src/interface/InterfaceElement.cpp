#include "../../lib/interface/InterfaceElement.h"

Orb::Orb(rendererType& r, textureType t, int posx, int posy, cameraType c) : Animated(r, t, ust.ORB_SIZE, ust.ORB_SIZE, c)
{
    mVisibleX = posx;
    mVisibleY = posy;
}

void Orb::render()
{
    Animated::clipUpdate();
    DGameObject::render();
}
