#include <SDL.h>

void close(SDL_Window*& window, SDL_Renderer*& renderer) // w argumentach wektor<weakptr> tekstur?
{
    // TODO Usuwanie tekstur

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    renderer = nullptr;

    IMG_Quit();
    SDL_Quit();
}