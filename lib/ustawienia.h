#ifndef USTAWIENIA
#define USTAWIENIA

#include <SDL.h>
#include <memory>

#include "destruktory.h"
#include "LTexture.h"

typedef std::unique_ptr<SDL_Window, WindowDeletor> windowType;
typedef std::unique_ptr<SDL_Renderer, RendererDeletor> rendererType;

typedef std::shared_ptr<LTexture> textureType;

class UST
{
public:

    const int SCREEN_WIDTH = 1700;
    const int SCREEN_HEIGHT = 800;

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