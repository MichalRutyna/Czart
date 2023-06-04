#include "../../lib/objects/Hero.h"

Hero::Hero(rendererType& r, textureType t, cameraType c) : PlayerMovable(r, t, c)
{
	mWidth = t->width();
	mHeight = t->height();
	mHp = 0;
}
