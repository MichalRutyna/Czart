#include "../../lib/objects/Enemy.h"
#include <random>

Enemy::Enemy(rendererType& r, textureType t_i, textureType t_r, textureType t_a, cameraType c) : Entity(r, t_i, c), Animated(t_i->width() / 8, t_i->height())
{
	mWidth = t_i->width() / 8;
	mHeight = t_i->height();
    VELOCITY = 0.4;

    texture_idle = t_i;
    texture_run = t_r;
    texture_attack = t_a;

    for (int i = 0; i < 7; i++)
    {
        attack_clips.push_back(std::make_shared<SDL_Rect>());

        attack_clips[i]->x = t_a->width() / 7 * i;
        attack_clips[i]->y = 0;
        attack_clips[i]->w = t_a->width() / 7;
        attack_clips[i]->h = t_a->height();
    }


    MAX_HP = 40;
    mHp = MAX_HP;

    MAX_MANA = 50;
    mMana = 0;

    ATTACK = 5;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 8000);

    mInternalX = dist6(rng);
    mInternalY = dist6(rng);
    mVisibleX = mInternalX;
    mVisibleY = mInternalY;

}


void Enemy::render()
{
    if (state == 1)
    {
        changeClip(attack_clips[mFrame / 5]);
        if (mFlip == -1) mVisibleX -= 100;
        Entity::render();
        mFrame++;
        if (mFrame / 5 >= 7)
        {
            mFrame = 0;
            state = 0;
            cooldown = 50;
            changeTexture(texture_idle);
        }
    }
    else if (state == 0)
    {
        changeClip(clips[mFrame / 5]);
        Entity::render();
        mFrame++;
        if (cooldown != 0) cooldown--;
        if (mFrame / 5 >= 8) mFrame = 0;
    }
}

void Enemy::update(int dt)
{
    if (state == 0)
    {
        int heroX, heroY;
        heroX = mHero->getX() + mHero->getWidth() / 2;
        heroY = mHero->getY() + mHero->getHeight() / 2;

        int myPosX, myPosY;
        myPosX = mVisibleX + mWidth / 2;
        myPosY = mVisibleY + mHeight / 2;

        if (heroX < myPosX) mVelX = -VELOCITY;
        if (heroX > myPosX) mVelX = VELOCITY;
        if (abs(heroX - myPosX) < 150) {
            mVelX = 0;
        };

        if (heroY < myPosY) mVelY = -VELOCITY;
        if (heroY > myPosY) mVelY = VELOCITY;
        if (abs(heroY - myPosY) < 10) {
            mVelY = 0;
        };

        if (mVelX < 0) changeFlip(-1);
        if (mVelX > 0) changeFlip(1);

        if (mVelX != 0 || mVelY != 0) changeTexture(texture_run);
        if (mVelX == 0 && mVelY == 0) changeTexture(texture_idle);

        if (abs(heroY - myPosY) < 10 && abs(heroX - myPosX) < 150)
        {
            attack();
        }
    }
    else if (state == 1)
    {
        mVelX = 0;
        mVelY = 0;
    }

    DMovable::update(dt);
}

void Enemy::setHero(std::shared_ptr<Hero> hero)
{
    mHero = hero;
}

void Enemy::attack()
{
    if (state == 0 && cooldown == 0)
    {
        state = 1;
        mFrame = 0;
        changeTexture(texture_attack);
        // TODO
        int side = mVisibleX + mWidth/2 - mHero->getX() - mHero->getWidth()/2;
        side < 0 ? mHero->takeDamage(ATTACK, -1) : mHero->takeDamage(ATTACK, 1);
            
    }
}
