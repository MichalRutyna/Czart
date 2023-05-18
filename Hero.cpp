#include "Hero.h"

UST& Ust = UST::pobierz_ustawienia();

Hero::Hero() : WIDTH(20), HEIGHT(30), NAME("Stachu Jones"), VELOCITY(10)
{
	memberPosX = 0;
	memberPosY = 0;

	memberVelX = 0;
	memberVelY = 0;
}

void Hero::handleEvent( SDL_Event& e )
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0){
		switch(e.key.keysym.sym)
		{
			case SDLK_UP: memberVelY -= VELOCITY; break;
			case SDLK_DOWN: memberVelY += VELOCITY; break;
			case SDLK_LEFT: memberVelX -= VELOCITY; break;
			case SDLK_RIGHT: memberVelX += VELOCITY; break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_UP: memberVelY += VELOCITY; break;
			case SDLK_DOWN: memberVelY -= VELOCITY; break;
			case SDLK_LEFT: memberVelX += VELOCITY; break;
			case SDLK_RIGHT: memberVelX -= VELOCITY; break;
		}
	}
}

void Hero::move()
{
	memberPosX += memberVelX;
	
	if( (memberPosX < 0) || (memberPosX + WIDTH > Ust.SCREEN_WIDTH) )
	{
		memberPosX -= memberVelX;
	}

	memberPosY += memberVelY;

	if ((memberPosY < 0) || (memberPosY + HEIGHT > Ust.SCREEN_HEIGHT))
	{
		memberPosY -= memberVelY;
	}
}

void Hero::render()
{
	std::cout << "Ale render";
}
