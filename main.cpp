#include <SDL.h>
#include <SDL_image.h>

#include "lib/ustawienia.h"
#include "lib/functionality/init.h"
#include "lib/functionality/close.h"

#include "lib/PlayerMovable.h"
#include "lib/functionality/LTexture.h"
#include "lib/functionality/LTimer.h"

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


    auto kamera = std::make_shared<Kamera>();
    // -----------------------------------------------------------------------------------
    auto stachu_tekstura = std::make_shared<LTexture>();
    stachu_tekstura->loadFromFile(renderer, "resources/rendertest.png", 300, 100);
    stachu_tekstura->setAlpha(160);

    auto stachu = std::make_shared<PlayerMovable>(renderer, stachu_tekstura, kamera);
    kamera->setFollow(stachu);
    // -----------------------------------------------------------------------------------
    auto kask_text = std::make_shared<LTexture>();
    kask_text->loadFromFile(renderer, "resources/czapka.png", 350, 35);
    auto kask = std::make_shared<Renderable>(renderer, kask_text, kamera);

    auto mieczyk_text = std::make_shared<LTexture>();
    mieczyk_text->loadFromFile(renderer, "resources/mieczyk.png", 100, 150);
    auto mieczyk = std::make_shared<Renderable>(renderer, mieczyk_text, kamera);
    // -----------------------------------------------------------------------------------
    auto background_txt = std::make_shared<LTexture>();
    background_txt->loadFromFile(renderer, "resources/background.png");
    auto background = std::make_shared<Renderable>(renderer, background_txt, kamera);
    // -----------------------------------------------------------------------------------

    std::vector<std::shared_ptr<Renderable>> obiektyProgramu;
    obiektyProgramu.push_back(stachu);
    obiektyProgramu.push_back(background);
    obiektyProgramu.push_back(mieczyk);
    obiektyProgramu.push_back(kask);

    // -----------------------------------------------------------------------------------
 
    std::vector<std::shared_ptr<Renderable>> movableObjects;

    // -----------------------------------------------------------------------------------
    auto frame_timer = std::make_shared<LTimer>();
    uint64_t accumulator = 0;
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

        // -----------------------------Movement------------------------------------------------
        accumulator += frame_timer->getTicks();
        frame_timer->start();

        while (accumulator >= ust.DT)
        {
            // Tu trzeba zrobiæ w³aœciwie listê wszystkiego co ma siê ruszaæ (zgodnie z fizyk¹, kamera chyba nie musi)
            stachu->move_step(ust.DT);
            accumulator -= ust.DT;
        }
        double alpha = static_cast<double>(accumulator) / ust.DT;
        stachu->move(alpha);

        // -----------------------------------------------------------------------------------

        kamera->update();


        // -----------------------------Render----------------------------------------------

        SDL_RenderClear(renderer.get()); //wyczysc

        background->render(0, 0);
        stachu->render();
        kask->render(stachu->getPosX()-25, stachu->getPosY()-10);
        mieczyk->render(stachu->getPosX()+55, stachu->getPosY()-50);

        SDL_RenderPresent(renderer.get()); //update
        

        // -----------------------------------------------------------------------------------
    }

    close();
    return 0;
}