#include "../../lib/rendering/Renderable.h"

Renderable::Renderable(rendererType& renderer, textureType texture, kameraType kamera) :
	mKamera(kamera), mTexture(texture) 
{
	mRenderer = &renderer;

	mClip = nullptr;
	mAngle = 0;
	mCenter = nullptr;
	mFlip = SDL_FLIP_NONE;
}

void Renderable::render(int posX, int posY)
{
	int renderX = posX;
	int renderY = posY;

	if (mKamera != nullptr) { // jeœli w konstruktorze nie podano kamery, obiekt jest umieszczany absolutnie
		renderX -= mKamera->getX();
		renderY -= mKamera->getY();
	}
	mTexture->render(*mRenderer, renderX, renderY, mClip, mAngle, mCenter, mFlip);
}

void Renderable::change_clip(int x, int y, int w, int h)
{
	if (mClip == nullptr) {
		mClip = std::make_shared<SDL_Rect>();
	}
	mClip->x = x;
	mClip->y = y;
	mClip->w = w;
	mClip->h = h;
}

void Renderable::change_angle(double angle)
{
	mAngle = angle;
}

void Renderable::change_center(int x, int y)
{
	if (mCenter == nullptr) {
		mCenter = std::make_shared<SDL_Point>();
	}
	mCenter->x = x;
	mCenter->y = y;
}

void Renderable::change_flip(TextureFlip flip)
{
	switch (flip)
	{
	case 0:
		mFlip = SDL_FLIP_NONE;
		break;
	case 1:
		mFlip = SDL_FLIP_HORIZONTAL;
		break;
	case 2:
		mFlip = SDL_FLIP_VERTICAL;
		break;
	default:
		break;
	}
}

int Renderable::getPosX()
{
	return xPosToRender;
}

int Renderable::getPosY()
{
	return yPosToRender;
}

int Renderable::width()
{
	return mWIDTH;
}

int Renderable::height()
{
	return mHEIGHT;
}

