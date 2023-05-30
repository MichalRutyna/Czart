#include <SDL.h>
#include <SDL_image.h>

#include "lib/ustawienia.h"
#include "lib/functionality/init.h"
#include "lib/functionality/close.h"
#include "lib/functionality/GameObjectHandler.h"
#include "lib/rendering/Kamera.h"
#include "lib/Tlo.h"

#include "lib/PlayerMovable.h"

#include <iostream>
#include <vector>


int main(int argc, char* argv[])
{
    static UST& ust = UST::pobierz_ustawienia();

    windowType window;
    rendererType renderer;

    // Initialization of window and renderer objects
    bool initialized = init(ust, window, renderer);
    if (!initialized) {
        std::cout << "Wystapil bl¹d przy inicjalizacji programu" << std::endl;
        return 0;
    }

    //Main loop flag
    bool quit = false;
    //Event handler
    SDL_Event e;

    // -----------------------------------------------------------------------------
    // Camera initialization
    auto kamera = std::make_shared<Kamera>();

    // ------------------------Texture initialization----------------------------------------
    auto stachu_tekstura = std::make_shared<LTexture>();
    stachu_tekstura->loadFromFile(renderer, "resources/rendertest.png", 300, 100);
    stachu_tekstura->setAlpha(160);
    
    auto kask_text = std::make_shared<LTexture>();
    kask_text->loadFromFile(renderer, "resources/czapka.png", 350, 35);

    auto mieczyk_text = std::make_shared<LTexture>();
    mieczyk_text->loadFromFile(renderer, "resources/mieczyk.png", 100, 150);
   
    auto background_txt = std::make_shared<LTexture>();
    background_txt->loadFromFile(renderer, "resources/background.png");

    std::cout << "Pomyslnie wczytano tekstury\n";

    // ---------------------------Object initialization-------------------------------------
    auto stachu = std::make_shared<PlayerMovable>(renderer, stachu_tekstura, kamera);
    //auto kask = std::make_shared<Renderable>(renderer, kask_text, kamera);
    //auto mieczyk = std::make_shared<Renderable>(renderer, mieczyk_text, kamera);
    auto background = std::make_shared<Tlo>(renderer, background_txt, kamera);

    std::cout << "Pomyslnie zainicjalizowano tekstury" << std::endl;

    // ---------------------------Creation of object layers--------------------------------
    GameObjectHandler objHandler;

    objHandler.subscribeBackground(background);
    objHandler.subscribePlayerLayer(stachu);
    objHandler.subscribeMoving(stachu);

    // ---------------------------Additional initialization--------------------------------
    kamera->setFollow(stachu);
 
    // ---------------------------Frame handling initialization----------------------------
    double accumulator = 0;
    uint64_t PerfCountFrequency = SDL_GetPerformanceFrequency();
    uint64_t start_time = SDL_GetPerformanceCounter(), end_time = 0; 
    double time_taken;

    // ------------------------------------------------------------------------------------
    std::cout << "Rozpoczynam petle zdarzen\n";
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
        end_time = SDL_GetPerformanceCounter();
        time_taken = ((double)(end_time - start_time) / (double)PerfCountFrequency) * 1000.0;
        //std::cout << 1.0 / (time_taken / 1000.0) <<  " ";
        accumulator += time_taken;
        start_time = end_time;

        while (accumulator >= ust.DT)
        {
            for (auto& object : objHandler.getMovingObjects())
            {
                object->update(ust.DT);
            }
            accumulator -= ust.DT;
        }
        double alpha = accumulator / ust.DT;
        for (auto& object : objHandler.getMovingObjects())
        {
            object->interpolate(alpha);
        }
        // -----------------------------Render----------------------------------------------

        kamera->update();

        SDL_RenderClear(renderer.get()); //wyczysc

        for (auto& element : objHandler.getBackgroundLayer())
        {
            element->render();
        }

        for (auto& element : objHandler.getPlayerLayer())
        {
            element->render();
        }

        for (auto& element : objHandler.getForegroundLayer())
        {
            element->render();
        }

        //kask->render(stachu->getPosX()-25, stachu->getPosY()-10);
        //mieczyk->render(stachu->getPosX()+55, stachu->getPosY()-50);

        SDL_RenderPresent(renderer.get()); //update

        // -----------------------------------------------------------------------------------
    }

    close();
    return 0;
}