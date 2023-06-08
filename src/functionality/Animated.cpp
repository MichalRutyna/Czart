#include "../../lib/functionality/Animated.h"


Animated::Animated(int clipW, int clipH) : mCLIP_WIDTH(clipW), mCLIP_HEIGHT(clipH)
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
    std::cout << "ee";
}
