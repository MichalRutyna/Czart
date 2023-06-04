#include "../../lib/functionality/Animated.h"


Animated::Animated(rendererType& r, textureType t, cameraType c) : DGameObject(r, t, c), mCLIP_WIDTH(0), mCLIP_HEIGHT(0)
{
    for (int i = 0; i < CLIPS_SIZE; i++)
    {
        clips.push_back(std::make_shared<SDL_Rect>());

        clips[i]->x = mCLIP_WIDTH * i;
        clips[i]->y = 0;

        clips[i]->w = mCLIP_WIDTH;
        clips[i]->h = mCLIP_HEIGHT;
    }
}

void Animated::clipUpdate()
{
    DGameObject::changeClip(clips[mFrame / 5]);
    mFrame++;
    if (mFrame / 5 >= 30) mFrame = 0;
}
