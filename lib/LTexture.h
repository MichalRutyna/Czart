#ifndef LTEXTURE
#define LTEXTURE

#include <string>
#include <SDL.h>
#include <SDL_Image.h>
#include <memory>

#include "ustawienia.h"

class LTexture 
{
public:
	LTexture();
	~LTexture();

	void mfree();

	bool loadFromFile(rendererType& renderer, std::string path, int scaled_width = -1, int scaled_height = -1);

	void render(rendererType& renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void setColor(uint8_t red, uint8_t green, uint8_t blue);

	void SetBlendMode(SDL_BlendMode blending);

	void setAlpha(uint8_t alpha);

	int width();
	int height();

private:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
};

#endif