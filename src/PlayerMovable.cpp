#include "../lib/PlayerMovable.h"

static UST& ust = UST::pobierz_ustawienia();


PlayerMovable::PlayerMovable(rendererType& renderer, textureType tekstura, kameraType kamera) : NAME("Stachu Jones"),
	DMovable(renderer, tekstura, kamera)
{
	mWidth = tekstura->width();
	mHeight = tekstura->height();
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
