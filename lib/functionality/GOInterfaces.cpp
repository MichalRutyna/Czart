#include "../../lib/functionality/GOInterfaces.h"

void _Drawable::changeClip(int x, int y, int w, int h)
{
	if (mClip == nullptr)
	{
		auto newClip = std::make_shared<SDL_Rect>();
		newClip->x = x;
		newClip->y = y;
		newClip->w = w;
		newClip->h = h;
		mClip = newClip;
	}
	else
	{
		mClip->x = x;
		mClip->y = y;
		mClip->w = w;
		mClip->h = h;
	}
}

void _Drawable::changeClip(std::shared_ptr<SDL_Rect> ref)
{
	mClip = ref;
}

void _Drawable::changeFlip(int side)
{
	if(side == -1) mFlip = SDL_FLIP_HORIZONTAL;
	if(side == 1) mFlip = SDL_FLIP_NONE;
}

void _Drawable::changeTexture(textureType texture)
{
	mTexture = texture;
}