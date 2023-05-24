#include "../lib/Hero.h"

UST& ust = UST::pobierz_ustawienia();

Hero::Hero(textureType tekstura) : mWIDTH(tekstura->width()), mHEIGHT(tekstura->height()), NAME("Stachu Jones"), VELOCITY(0.5 * ust.VELOCITY_MULTIPLIER), tekstura(tekstura)
{
	mPosX = 0;
	mPosY = 0;

	mVelX = 0;
	mVelY = 0;

	oldX = mPosX;
	oldY = mPosY;
}

void Hero::handleEvent( SDL_Event& e )
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0){
		switch(e.key.keysym.sym)
		{
			case SDLK_UP: mVelY -= VELOCITY; break;
			case SDLK_DOWN: mVelY += VELOCITY; break;
			case SDLK_LEFT: mVelX -= VELOCITY; break;
			case SDLK_RIGHT: mVelX += VELOCITY; break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_UP: mVelY += VELOCITY; break;
			case SDLK_DOWN: mVelY -= VELOCITY; break;
			case SDLK_LEFT: mVelX += VELOCITY; break;
			case SDLK_RIGHT: mVelX -= VELOCITY; break;
		}
	}
}

void Hero::move_step(int timeStep_ms)
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

void Hero::move(double alpha)
{
	mPosY = (mPosY * alpha) + (oldY * (1.0 - alpha));
	mPosX = (mPosX * alpha) + (oldX * (1.0 - alpha));
}

void Hero::render(rendererType& renderer, int camX, int camY)
{
	tekstura->render(renderer, static_cast<int>(mPosX - camX), static_cast<int>(mPosY - camY));
}

double Hero::getPosX()
{
	return mPosX;
}

double Hero::getPosY()
{
	return mPosY;
}

int Hero::width()
{
	return mWIDTH;
}

int Hero::height()
{
	return mHEIGHT;
}