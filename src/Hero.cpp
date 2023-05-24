#include "../lib/Hero.h"

UST& ust = UST::pobierz_ustawienia();

Hero::Hero(textureType tekstura) : mWIDTH(tekstura->width()), mHEIGHT(tekstura->height()), NAME("Stachu Jones"), VELOCITY(0.5 * ust.VELOCITY_MULTIPLIER), tekstura(tekstura)
{
	mPosX = 0;
	mPosY = 0;

	mVelX = 0;
	mVelY = 0;
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

void Hero::move(int timeStep_ms, double alpha)
{	
	double newX = mPosX, newY = mPosY;

	newX += mVelX * timeStep_ms;
	
	if (newX < 0)
	{
		newX = 0;
	}
	else if (newX + mWIDTH > ust.LEVEL_WIDTH)
	{
		newX = static_cast<double>(ust.LEVEL_WIDTH - mWIDTH);
	}

	newY += mVelY * timeStep_ms;

	if (newY < 0)
	{
		newY = 0;
	}
	else if (newY + mHEIGHT > ust.LEVEL_HEIGHT)
	{
		newY = static_cast<double>(ust.LEVEL_HEIGHT - mHEIGHT);
	}

	mPosX = (mPosX * alpha) + (newX * (1.0 - alpha));
	mPosY = (mPosY * alpha) + (newY * (1.0 - alpha));
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