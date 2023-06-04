#include "../../lib/objects/Hero.h"

Hero::Hero(rendererType& r, textureType t_i, textureType t_r, textureType t_a,  cameraType c) : PlayerMovable(r, t_i, t_r, t_a, c)
{
	mWidth = t_i->width();
	mHeight = t_i->height();
	for (int i = 0; i < CLIPS_SIZE; i++)
    {
        clips.push_back(std::make_shared<SDL_Rect>());

        clips[i]->x = 231 * i;
        clips[i]->y = 0;
        clips[i]->w = 231;
        clips[i]->h = 278;
    }
	mHp = 0;
}

void Hero::render()
{
	DMovable::changeClip(clips[mFrame / 8]);
	DMovable::render();
	mFrame++;
	if (mFrame / 8 >= CLIPS_SIZE) mFrame = 0;
}

void Hero::handleEvent(SDL_Event& e)
{
	if(e.key.keysym.sym == SDLK_SPACE)
	DMovable::changeTexture(texture_attack);
}