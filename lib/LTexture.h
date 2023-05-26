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
	virtual ~LTexture();

	void mfree();

	bool loadFromFile(rendererType& renderer, std::string path, int scaled_width = -1, int scaled_height = -1);

	void render(rendererType& renderer, int x, int y, std::shared_ptr<SDL_Rect> clip = nullptr, double angle = 0.0f,
			std::shared_ptr<SDL_Point> center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void setColor(uint8_t red, uint8_t green, uint8_t blue);

	void SetBlendMode(SDL_BlendMode blending);

	void setAlpha(uint8_t alpha);

	int width();
	int height();

	void changeSize(int w, int h);

private:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
};

#endif