#ifndef DESTRUKTORY
#define DESTRUKTORY

#include <SDL.h>
#include <iostream>

struct WindowDeletor {
    void operator()(SDL_Window* okno) {
        std::cout << "Usunieto okno" << std::endl;
        SDL_DestroyWindow(okno);
        okno = nullptr;
    }
};

struct RendererDeletor {
    void operator()(SDL_Renderer* renderer) {
        std::cout << "Usunieto renderer" << std::endl;
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
};

#endif
