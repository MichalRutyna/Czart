#include "../lib/Hero.h"

UST& Ust = UST::pobierz_ustawienia();

Hero::Hero(LTexture* tekstura) : WIDTH(tekstura->width()), HEIGHT(tekstura->height()), NAME("Stachu Jones"), VELOCITY(10), tekstura(tekstura)
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

void Hero::move()
{
	mPosX += mVelX;
	
	if( (mPosX < 0) || (mPosX + WIDTH > Ust.SCREEN_WIDTH) )
	{
		mPosX -= mVelX;
	}

	mPosY += mVelY;

	if ((mPosY < 0) || (mPosY + HEIGHT > Ust.SCREEN_HEIGHT))
	{
		mPosY -= mVelY;
	}
}

void Hero::render(SDL_Renderer* renderer)
{
	tekstura->render(renderer, mPosX, mPosY);
}
