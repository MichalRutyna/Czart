#include "../../lib/interface/InterfaceElement.h"

Orb::Orb(rendererType& r, textureType t, int posx, int posy, cameraType c) : Animated(r, t, c)
{
    mVisibleX = posx;
    mVisibleY = posy;

    mCLIP_WIDTH = ust.ORB_SIZE;
    mCLIP_HEIGHT = ust.ORB_SIZE;
}
