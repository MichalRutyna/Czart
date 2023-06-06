#include "../../lib/objects/Enemy.h"

Enemy::Enemy(rendererType& r, textureType t_i, textureType t_r, textureType t_a, cameraType c) : Entity(r, t_i, c), Animated(t_i->width()/8, t_i->height())
{
	mWidth = t_i->width() / 8;
	mHeight = t_i->height();
    VELOCITY = 0.4;

    texture_idle = t_i;
    texture_run = t_r;
    texture_attack = t_a;
}


void Enemy::render()
{
    Entity::changeClip(clips[mFrame / 5]);
    mFrame++;
    if (mFrame / 5 >= 8) mFrame = 0;
    Entity::render();
}

void Enemy::update(int dt)
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
        state = 1;
    };
    
    if (heroY < myPosY) mVelY = -VELOCITY;
    if (heroY > myPosY) mVelY = VELOCITY;
    if (abs(heroY - myPosY) < 10) {
        mVelY = 0;
        state = 1;
    };

    if (mVelX < 0) DMovable::changeFlip(-1);
    if (mVelX > 0) DMovable::changeFlip(1);

    if (mVelX != 0 || mVelY != 0) DMovable::changeTexture(texture_run);
    if (mVelX == 0 && mVelY == 0) DMovable::changeTexture(texture_idle);


    DMovable::update(dt);
}

void Enemy::setHero(std::shared_ptr<Hero> hero)
{
    mHero = hero;
}
