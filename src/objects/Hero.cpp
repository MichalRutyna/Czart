#include "../../lib/objects/Hero.h"

Hero::Hero(rendererType& r, textureType t, cameraType c) : PlayerMovable(r, t, c)
{
	mHp = 0;
}
