#include <SDL.h>
// #include <SDL_image.h>
#include "lib/ustawienia.h"
#include "lib/ustawienia.h"
#include "lib/Hero.h"

#include <iostream>
#include <vector>

using namespace std;
UST& ust = UST::pobierz_ustawienia();


void close(SDL_Window*& window)
{
    // TODO Usuwanie tekstur

    SDL_DestroyWindow(window);
    window = nullptr;

    //IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    SDL_Window* window = NULL;

    SDL_Surface* screenSurface = NULL;

    SDL_Surface* gHelloWorld = NULL; // OBRAZEK

    SDL_Surface* optimizedSurface = NULL; // OBRAZEK WYJSCIA

    SDL_Surface* exit = NULL; // OBRAZEK WYJSCIA

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Eroor: %s\n", SDL_GetError());
    }
    else
    {
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ust.SCREEN_WIDTH, ust.SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface(window);

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
            SDL_UpdateWindowSurface(window);

            //Hack to get window to stay up
        }
    }
    exit = SDL_LoadBMP("resources/exit.bmp");
    //Apply the image
    SDL_BlitSurface(exit, NULL, screenSurface, NULL);

    //Update the surface
    SDL_UpdateWindowSurface(window);
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_KEYDOWN)
            {
                quit = true;
            }
        }
    }

    //Potem siê chyba nie u¿ywa surface wiêc jeszcze tu zostawiam
    

    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_Quit();

    return 0;
}