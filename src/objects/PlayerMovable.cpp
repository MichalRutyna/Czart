#include "../../lib/objects/PlayerMovable.h"
#include <SDL.h>

PlayerMovable::PlayerMovable(rendererType& r, textureType t_i, textureType t_r, textureType t_a, cameraType c) : Entity(r, t_i, c)
{
	texture_idle = t_i;
	texture_run = t_r;
	texture_attack = t_a;
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
	if (mVelX!=0 || mVelY!=0) PlayerMovable::changeTexture(PlayerMovable::texture_run);
	if (mVelX > 0) PlayerMovable::changeFlip(1);
	if (mVelX < 0) PlayerMovable::changeFlip(-1);
	if (mVelX == 0 && mVelY == 0) PlayerMovable::changeTexture(PlayerMovable::texture_idle);
}
