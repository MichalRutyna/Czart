#include "../../lib/functionality/GameObjects.h"


void Movable::update(const int deltaTime)
{
	move_step(deltaTime);
}

void Movable::interpolate(const double alpha)
{
	move(alpha);
}

void Movable::move_step(int timeStep_ms)
{
	mInPreviousX = mInternalX;
	mInPreviousX = mInternalX;

	mInternalX += mVelX * timeStep_ms;
	mInternalX += mVelY * timeStep_ms;

	handleCollisions();

}

void Movable::handleCollisions()
{
	if (mInternalX < 0)
	{
		mInternalX = 0;
	}
	else if (mInternalX + mWidth > ust.LEVEL_WIDTH)
	{
		mInternalX = static_cast<double>(ust.LEVEL_WIDTH - mWidth);
	}

	if (mInternalY < 0)
	{
		mInternalY = 0;
	}
	else if (mInternalY + mHeight > ust.LEVEL_HEIGHT)
	{
		mInternalY = static_cast<double>(ust.LEVEL_HEIGHT - mHeight);
	}


}

void Movable::move(double alpha)
{
	mVisibleX = (mInternalX * alpha) + (mInPreviousX * (1.0 - alpha));
	mVisibleY = (mInternalY * alpha) + (mInPreviousY * (1.0 - alpha));
}

void DMovable::render()
{
	int tempX = mVisibleX;
	int tempY = mVisibleY;

	if (mKamera != nullptr) { 
		tempX -= static_cast<int>(mKamera->getX());
		tempY -= static_cast<int>(mKamera->getY());
	}
	mTexture->render(*mRenderer, static_cast<int>(round(tempX)), static_cast<int>(round(tempY)), mClip, mAngle, mCenter, mFlip);
}
