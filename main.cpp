#include <SDL.h>
#include <SDL_image.h>

#include "lib/ustawienia.h"
#include "lib/functionality/init.h"
#include "lib/functionality/close.h"

#include "lib/PlayerMovable.h"

#include <iostream>
#include <vector>

using namespace std;


int main(int argc, char* argv[])
{
    UST& ust = UST::pobierz_ustawienia();

    windowType window;
    rendererType renderer;

    // Initialization of window and renderer objects
    bool initialized = init(ust, window, renderer);
    if (!initialized) {
        std::cout << "Wyst¹pi³ b³¹d przy inicjalizacji programu" << std::endl;
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
    auto kask = std::make_shared<Renderable>(renderer, kask_text, kamera);
    auto mieczyk = std::make_shared<Renderable>(renderer, mieczyk_text, kamera);
    auto background = std::make_shared<Renderable>(renderer, background_txt, kamera);

    // ---------------------------Creation of object layers-------------------------------

    std::vector<std::shared_ptr<GameObject>> backgroundLayer;   // background only
    std::vector<std::shared_ptr<GameObject>> playerLayer;       // player, monsters, walls
    std::vector<std::shared_ptr<GameObject>> foregroundLayer;   // things which should obstruct view
    
    // TODO GameObjectHandler[3];
    // -----------------------------------------------------------------------------------
    kamera->setFollow(stachu);
 
    std::vector<std::shared_ptr<Moving>> movableObjects;
    movableObjects.push_back(stachu);

    // -----------------------------------------------------------------------------------
    double accumulator = 0;
    uint64_t PerfCountFrequency = SDL_GetPerformanceFrequency();
    uint64_t start_time = SDL_GetPerformanceCounter(), end_time = 0; 
    double time_taken;
    // -----------------------------------------------------------------------------------
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
        accumulator += time_taken;
        start_time = end_time;

        while (accumulator >= ust.DT)
        {
            for (auto& object : movableObjects)
            {
                object->move_step(ust.DT);
            }
            accumulator -= ust.DT;
        }
        double alpha = accumulator / ust.DT;
        for (auto& object : movableObjects)
        {
            object->move(alpha);
        }
        // -----------------------------Render----------------------------------------------

        kamera->update();

        SDL_RenderClear(renderer.get()); //wyczysc

        for (auto& element : backgroundLayer)
        {
        }
        stachu->render();
        //kask->render(stachu->getPosX()-25, stachu->getPosY()-10);
        //mieczyk->render(stachu->getPosX()+55, stachu->getPosY()-50);

        SDL_RenderPresent(renderer.get()); //update

        // -----------------------------------------------------------------------------------
    }

    close();
    return 0;
}