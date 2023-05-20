#include <SDL.h>
#include <SDL_image.h>

#include "lib/ustawienia.h"
#include "lib/init.h"
#include "lib/close.h"

#include "lib/Hero.h"
#include "lib/LTexture.h"

#include <iostream>
#include <vector>

using namespace std;


int main(int argc, char* argv[])
{
    UST& ust = UST::pobierz_ustawienia();

    windowType window;
    rendererType renderer;


    bool initialized = init(ust, window, renderer);

    if (!initialized) {
        std::cout << "Wyst¹pi³ b³¹d przy inicjalizacji programu" << std::endl;
        return 0;
    }

    // ------------------------------------------------------
    // Poni¿ej tego, wszystko do testów

    SDL_Surface* screenSurface = NULL;

    SDL_Surface* gHelloWorld = NULL; // OBRAZEK

    SDL_Surface* optimizedSurface = NULL; // OBRAZEK WYJSCIA

    SDL_Surface* exit = NULL; // OBRAZEK WYJSCIA

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;

    //Get window surface
    screenSurface = SDL_GetWindowSurface(window.get());

    gHelloWorld = SDL_LoadBMP("resources/hello_world.bmp");
    optimizedSurface = SDL_ConvertSurface(gHelloWorld, screenSurface->format, 0);
    SDL_FreeSurface(gHelloWorld);
    if (gHelloWorld == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", "resources/hello_world.bmp", SDL_GetError());
    }
    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = ust.SCREEN_WIDTH;
    stretchRect.h = ust.SCREEN_HEIGHT;
    SDL_BlitScaled(optimizedSurface, NULL, screenSurface, &stretchRect);
    SDL_UpdateWindowSurface(window.get());

    exit = SDL_LoadBMP("resources/exit.bmp");
    //Apply the image
    SDL_BlitSurface(exit, NULL, screenSurface, NULL);
    //Update the surface
    SDL_UpdateWindowSurface(window.get());

    // -----------------------------------------------------------------------------------
    auto stachu_tekstura = new LTexture();
    stachu_tekstura->loadFromFile(renderer, "resources/rendertest.bmp");

    auto stachu = new Hero(stachu_tekstura);
    // -----------------------------------------------------------------------------------

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            stachu->handleEvent(e);
        }

        // -----------------------------------------------------------------------------------

        stachu->move();


        SDL_RenderClear(renderer.get()); //wyczysc

        stachu->render(renderer); //zrenderuj

        SDL_RenderPresent(renderer.get()); //update
        

        // -----------------------------------------------------------------------------------
    }

    close();

    return 0;
}