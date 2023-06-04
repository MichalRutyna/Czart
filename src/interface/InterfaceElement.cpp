#include "../../lib/interface/InterfaceElement.h"

Orb::Orb(rendererType& r, textureType t, int posx, int posy, cameraType c) : DGameObject(r, t, c)
{
    for (int i = 0; i < CLIPS_SIZE; i++)
    {
        clips.push_back(std::make_shared<SDL_Rect>());

        clips[i]->x = ust.ORB_SIZE * i;
        clips[i]->y = 0;

        clips[i]->w = ust.ORB_SIZE;
        clips[i]->h = ust.ORB_SIZE;
    }
    mVisibleX = posx;
    mVisibleY = posy;
}

void Orb::render()
{
    DGameObject::changeClip(clips[mFrame / 5]);
    DGameObject::render();
    mFrame++;
    if (mFrame / 5 >= 30) mFrame = 0;
}
