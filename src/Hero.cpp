#include "../lib/Hero.h"

UST& Ust = UST::pobierz_ustawienia();

Hero::Hero(textureType tekstura) : WIDTH(tekstura->width()), HEIGHT(tekstura->height()), NAME("Stachu Jones"), VELOCITY(10), tekstura(tekstura)
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

void Hero::move() //szpara sie robi przez rozdzielczosc teksturki i rozdzielczosc monitora xd
{
	mPosX += mVelX;
	
	if( (mPosX < 0) || (mPosX + WIDTH > Ust.LEVEL_WIDTH) )
	{
		mPosX -= mVelX;
	}
	mPosY += mVelY;

	if ((mPosY < 0) || (mPosY + HEIGHT > Ust.LEVEL_HEIGHT))
	{
		mPosY -= mVelY;
	}
}

void Hero::render(rendererType& renderer, int camX, int camY)
{
	tekstura->render(renderer, mPosX - camX, mPosY - camY);
}

int Hero::getPosX()
{
	return mPosX;
}

int Hero::getPosY()
{
	return mPosY;
}

int Hero::heroWidth()
{
	return WIDTH;
}

int Hero::heroHeight()
{
	return HEIGHT;
}