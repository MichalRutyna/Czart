#ifndef USTAWIENIA
#define USTAWIENIA

#include <SDL.h>
#include <memory>

#include "destruktory.h"

typedef std::unique_ptr<SDL_Window, WindowDeletor> windowType;
typedef std::unique_ptr<SDL_Renderer, RendererDeletor> rendererType;

typedef class LTexture LTexture;
typedef class Kamera Kamera;

typedef std::shared_ptr<LTexture> textureType;
typedef std::shared_ptr<Kamera> kameraType;

class UST
{
public:
    const int SCREEN_WIDTH = 1600;
    const int SCREEN_HEIGHT = 800;
	const int LEVEL_WIDTH = 8000;
	const int LEVEL_HEIGHT = 8000;
	const int DT = 10;
	const float VELOCITY_MULTIPLIER = 2;
private:
	UST() {}
	UST(const UST&);
public:
	static UST & pobierz_ustawienia(){
		static UST ustawienia;
		return ustawienia;
	}
};

#endif