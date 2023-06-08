#include "../../lib/objects/Hero.h"

Hero::Hero(rendererType& r, textureType t_i, textureType t_r, textureType t_a,  cameraType c) : PlayerMovable(r, t_i, t_r, t_a, c)
{
    mInternalX = 2000;
    mInternalY = 2000;

    MAX_HP = 100;
    mHp = 100;

    MAX_MANA = 100;
    mMana = 100;

    ATTACK = 20;

	mWidth = t_i->width() / 8;
	mHeight = t_i->height();
	for (int i = 0; i < CLIPS_SIZE; i++)
    {
        clips.push_back(std::make_shared<SDL_Rect>());

        clips[i]->x = 231 * i;
        clips[i]->y = 0;
        clips[i]->w = 231;
        clips[i]->h = 278;
    }
    for (int i = 0; i < 7; i++)
    {
        attack_clips.push_back(std::make_shared<SDL_Rect>());

        attack_clips[i]->x = 318 * i;
        attack_clips[i]->y = 0;
        attack_clips[i]->w = 318;
        attack_clips[i]->h = 278;
    }
}

void Hero::render()
{
    if (state == 0)
    {
        DMovable::changeClip(clips[mFrame / 8]);
        DMovable::render();
        mFrame++;
        if (mFrame / 8 >= CLIPS_SIZE) mFrame = 0;
    }
    else if (state == 1)
    {
        changeTexture(texture_attack);
        DMovable::changeClip(attack_clips[mFrame / 7]);
        if(facing == -1) Hero::mVisibleX -= 100;
        DMovable::render();
        mFrame++;
        if (mFrame / 7 >= 7)
        {
            mFrame = 0;
            state = 0;
            changeTexture(texture_idle);
        }   
    }
    if (mMana < MAX_MANA && mFrame%6 == 0) mMana++;
}

void Hero::handleEvent(SDL_Event& e)
{
    if (e.key.keysym.sym == SDLK_SPACE && e.key.repeat == 0 && e.type == SDL_KEYDOWN && getMana()>=20)
    {
        state = 1;
        mFrame = 0;
        mMana -= 20;
    }
    PlayerMovable::handleEvent(e);
}