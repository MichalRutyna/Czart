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
  
    auto kask_text = std::make_shared<LTexture>();
    kask_text->loadFromFile(renderer, "resources/czapka.png", 350, 35);

    auto mieczyk_text = std::make_shared<LTexture>();
    mieczyk_text->loadFromFile(renderer, "resources/mieczyk.png", 100, 150);
   
    auto background_txt = std::make_shared<LTexture>();
    background_txt->loadFromFile(renderer, "resources/background.png");

    std::cout << "Pomyslnie wczytano tekstury\n";

    // -------------------------------Kule------------------------------------------------
    int rozmiar_kuli = 150;

    auto orb_border_text = std::make_shared<LTexture>();
    orb_border_text->loadFromFile(renderer, "resources/obramowka.png", rozmiar_kuli+5, rozmiar_kuli+5);
    auto orb_border = std::make_shared<Renderable>(renderer, orb_border_text);

    SDL_Rect hpClips[30];
    LTexture hp_texture, mana_texture;
    
    hp_texture.loadFromFile(renderer, "resources/kula_hp.png", 30*rozmiar_kuli, rozmiar_kuli);
    mana_texture.loadFromFile(renderer, "resources/kula_mana.png", 30 * rozmiar_kuli, rozmiar_kuli);


    for (int i = 0; i < 30; i++)
    {
        hpClips[i].x = rozmiar_kuli *i;
        hpClips[i].y = 0;
        hpClips[i].w = rozmiar_kuli;

        hpClips[i].h = rozmiar_kuli;
    }

    // ---------------------------Object initialization-------------------------------------
    auto stachu = std::make_shared<PlayerMovable>(renderer, stachu_tekstura, kamera);
    //auto kask = std::make_shared<Renderable>(renderer, kask_text, kamera);
    //auto mieczyk = std::make_shared<Renderable>(renderer, mieczyk_text, kamera);
    auto background = std::make_shared<Tlo>(renderer, background_txt, kamera);

    std::cout << "Pomyslnie zainicjalizowano obiekty" << std::endl;

    int hp_frame = 0;
    int i = 0;
    // ---------------------------Creation of object layers--------------------------------
    GameObjectHandler objHandler;

    objHandler.subscribeBackground(background);
    objHandler.subscribePlayerLayer(stachu);
    objHandler.subscribeUpdatable(stachu);

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
        std::shared_ptr<SDL_Rect> currentClip = std::make_shared<SDL_Rect>(hpClips[hp_frame / 5]);
        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN)
            {
                i++;
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
            for (auto& object : objHandler.getUpdatableObjects())
            {
                object->update(ust.DT);
            }
            accumulator -= ust.DT;
        }
        double alpha = accumulator / ust.DT;
        for (auto& object : objHandler.getUpdatableObjects())
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
      
        currentClip->y = 0 + i * 20;
        currentClip->h = 150 - i * 20;
        
        hp_texture.render(renderer, 100, ust.SCREEN_HEIGHT - 202 + i*20, currentClip);
        mana_texture.render(renderer, 1300, ust.SCREEN_HEIGHT - 202 + i*20, currentClip);
        hp_frame++;
        if (hp_frame/5 >= 30) hp_frame = 0;
        orb_border->render(98, ust.SCREEN_HEIGHT - 204); // hp
        orb_border->render(1300, ust.SCREEN_HEIGHT - 204); // mana
      
        //kask->render(stachu->getPosX()-25, stachu->getPosY()-10);
        //mieczyk->render(stachu->getPosX()+55, stachu->getPosY()-50);

        SDL_RenderPresent(renderer.get()); //update

        // -----------------------------------------------------------------------------------
        
       // kask->change_angle(i);
       // stachu->change_angle(i);
        //i+=0.1;
    }
    close();
    return 0;
}