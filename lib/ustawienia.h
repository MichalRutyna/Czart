#ifndef USTAWIENIA
#define USTAWIENIA

#include <SDL.h>
#include <memory>

#include "destruktory.h"

typedef std::unique_ptr<SDL_Window, WindowDeletor> windowType;
typedef std::unique_ptr<SDL_Renderer, RendererDeletor> rendererType;

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