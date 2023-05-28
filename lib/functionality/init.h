#include "SDL.h"

#include <iostream>
#include <memory>

#include "../ustawienia.h"

bool init(UST& ust, windowType& window, rendererType& renderer)
{
    // Inicjalizacja SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Nie mozna bylo zainicjalizowac SDL, SDL Error: " << SDL_GetError();
        return false;
    }


    // Liniowe filtrowanie tekstur
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        std::cout << "Uwaga! Liniowe filtrowanie tekstur wylaczone!";
    }

    // Tworzenie okna
    window.reset(SDL_CreateWindow("Czart", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ust.SCREEN_WIDTH, ust.SCREEN_HEIGHT, SDL_WINDOW_SHOWN));
    if (window == NULL) {
        std::cout << "Nie mozna stworzyc okna, SDL Error: " << SDL_GetError();
        return false;
    }


    // Tworzenie renderatora z vsynciem
    renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
    if (renderer == NULL) {
        std::cout << "Nie mozna zainicjalizowac renderatora, SDL Error: " << SDL_GetError();
        return false;
    }

    // Inicjalizacja koloru renderatora
    SDL_SetRenderDrawColor(renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);

 
    // Inicjalizacja wczytywania PNG
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "Nie mozna zainicjalizowac SDL_image, SDL_image Error: " << IMG_GetError();
        return false;
    }


    // Wszystko zainicjalizowane poprawnie
    std::cout << "Inicjalizacja zakonczona pomyslnie" << std::endl;
    return true;
}
