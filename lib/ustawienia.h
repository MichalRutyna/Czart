#ifndef USTAWIENIA
#define USTAWIENIA

#include <SDL.h>
#include <memory>

#include "functionality/destruktory.h"

typedef std::unique_ptr<SDL_Window, WindowDeletor> windowType;
typedef std::unique_ptr<SDL_Renderer, RendererDeletor> rendererType;

typedef class LTexture LTexture;
typedef class Kamera Kamera;

typedef std::shared_ptr<LTexture> textureType;
typedef std::shared_ptr<Kamera> kameraType;

typedef enum {
	none = 0,
	horizontal = 1,
	vertical = 2
} TextureFlip;

class UST
{
public:
    static const int SCREEN_WIDTH = 1600;
    static const int SCREEN_HEIGHT = 800;
	static const int LEVEL_WIDTH = 8000;
	static const int LEVEL_HEIGHT = 8000;
	static const int DT = 10;
	const float VELOCITY_MULTIPLIER = 2.0f;

private:
	UST() {}
	UST(const UST&);
public:
	~UST() { 
		std::cout << "Usunieto ustawienia\n";
		
	}
	static UST & pobierz_ustawienia(){
		static UST ustawienia;
		return ustawienia;
	}
};

#endif