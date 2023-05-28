#include "../../lib/rendering/Moving.h"

UST& ust = UST::pobierz_ustawienia();

Moving::Moving(double velocity) : VELOCITY(velocity)
{
	mPosX = 0;
	mPosY = 0;

	mVelX = 0;
	mVelY = 0;

	oldX = mPosX;
	oldY = mPosY;

	xPosToRender = mPosX;
	yPosToRender = mPosY;

	mWIDTH = 0;
	mHEIGHT = 0;
}

void Moving::move_step(int timeStep_ms)
{
	oldX = mPosX;
	oldY = mPosY;

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
	xPosToRender = static_cast<int>((mPosX * alpha) + (oldX * (1.0 - alpha)));
	yPosToRender = static_cast<int>((mPosY * alpha) + (oldY * (1.0 - alpha)));
	std::cout << "Moving: " << xPosToRender << "x" << yPosToRender << std::endl;
}
