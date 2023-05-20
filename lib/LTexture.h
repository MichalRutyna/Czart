#ifndef LTEXTURE
#define LTEXTURE

#include <string>
#include <SDL.h>
#include <memory>

#include "ustawienia.h"

class LTexture 
{
public:
	LTexture();
	~LTexture();

	void mfree();

	bool loadFromFile(rendererType& renderer, std::string path);

	void render(rendererType& renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int width();
	int height();

private:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
};

#endif