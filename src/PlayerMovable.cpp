#include "../lib/PlayerMovable.h"

UST& ust = UST::pobierz_ustawienia();

PlayerMovable::PlayerMovable(rendererType& renderer, kameraType kamera, textureType tekstura) : mWIDTH(tekstura->width()), mHEIGHT(tekstura->height()),
	NAME("Stachu Jones"), VELOCITY(0.5 * ust.VELOCITY_MULTIPLIER),
	Renderable(renderer, kamera, tekstura)
{
	mPosX = 0;
	mPosY = 0;

	mVelX = 0;
	mVelY = 0;

	oldX = mPosX;
	oldY = mPosY;

	newX = mPosX;
	newY = mPosY;
}

void PlayerMovable::handleEvent( SDL_Event& e )
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

void PlayerMovable::move_step(int timeStep_ms)
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

void PlayerMovable::move(double timestep_alpha)
{
	newX = (mPosX * timestep_alpha) + (oldX * (1.0 - timestep_alpha));
	newY = (mPosY * timestep_alpha) + (oldY * (1.0 - timestep_alpha));
}

void PlayerMovable::render()
{
	Renderable::render(static_cast<int>(newX), static_cast<int>(newY));
}

double PlayerMovable::getPosX()
{
	return newX;
}

double PlayerMovable::getPosY()
{
	return newY;
}

int PlayerMovable::width()
{
	return mWIDTH;
}

int PlayerMovable::height()
{
	return mHEIGHT;
}