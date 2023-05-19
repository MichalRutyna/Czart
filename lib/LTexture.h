#ifndef LTEXTURE
#define LTEXTURE

#include <string>
#include <SDL.h>

class LTexture 
{
public:
	LTexture();
	~LTexture();

	void free();

	bool loadFromFile(SDL_Renderer * renderer, std::string path);

	void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int width();
	int height();

private:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
};

#endif