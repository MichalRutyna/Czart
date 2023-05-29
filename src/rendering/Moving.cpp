#include "../../lib/rendering/Moving.h"
#include <math.h>

UST& ust = UST::pobierz_ustawienia();

Moving::Moving(double velocity) : VELOCITY(velocity)
{
	mPosX = 0.0;
	mPosY = 0.0;

	mVelX = 0;
	mVelY = 0;

	previousX = mPosX;
	previousY = mPosY;

	visibleX = (float)mPosX;
	visibleY = (float)mPosY;

	mWIDTH = 0;
	mHEIGHT = 0;
}

void Moving::move_step(int timeStep_ms)
{
	previousX = mPosX;
	previousY = mPosY;

	mPosX += mVelX * timeStep_ms;

	if (mPosX < 0)
	{
		mPosX = 0;
	}
	else if (mPosX + mWIDTH > ust.LEVEL_WIDTH)
	{
		mPosX = static_cast<double>(ust.LEVEL_WIDTH - mWIDTH);
	}

	mPosY += mVelY * timeStep_ms;

	if (mPosY < 0)
	{
		mPosY = 0;
	}
	else if (mPosY + mHEIGHT > ust.LEVEL_HEIGHT)
	{
		mPosY = static_cast<double>(ust.LEVEL_HEIGHT - mHEIGHT);
	}
}

void Moving::move(double alpha)
{
	visibleX = (mPosX * alpha) + (previousX * (1.0 - alpha));
	visibleY = (mPosY * alpha) + (previousY * (1.0 - alpha));
}