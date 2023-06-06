#include <SDL.h>
#include <SDL_image.h>

#include "lib/ustawienia.h"
#include "lib/functionality/init.h"
#include "lib/functionality/close.h"
#include "lib/functionality/GameObjectHandler.h"
#include "lib/rendering/Kamera.h"
#include "lib/objects/Tlo.h"
#include "lib/interface/InterfaceElement.h"

#include "lib/objects/Hero.h"
#include "lib/objects/Enemy.h"

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
        std::cout << "Wystapil blad przy inicjalizacji programu" << std::endl;
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
    auto stachu_tekstura_idle = std::make_shared<LTexture>();
    stachu_tekstura_idle->loadFromFile(renderer, "resources/player_idle.png");
    auto stachu_tekstura_run = std::make_shared<LTexture>();
    stachu_tekstura_run->loadFromFile(renderer, "resources/player_run.png");
    auto stachu_tekstura_attack = std::make_shared<LTexture>();
    stachu_tekstura_attack->loadFromFile(renderer, "resources/player_attack.png");

    auto enemy_texture_idle = std::make_shared<LTexture>();
    enemy_texture_idle->loadFromFile(renderer, "resources/enemy_idle.png", 924, 139);
    auto enemy_texture_run = std::make_shared<LTexture>();
    enemy_texture_run->loadFromFile(renderer, "resources/enemy_run.png", 924, 139);
    auto enemy_texture_attack = std::make_shared<LTexture>();
    enemy_texture_attack->loadFromFile(renderer, "resources/enemy_attack.png", 1113, 139);

    auto kask_text = std::make_shared<LTexture>();
    kask_text->loadFromFile(renderer, "resources/czapka.png", 350, 35);

    auto mieczyk_text = std::make_shared<LTexture>();
    mieczyk_text->loadFromFile(renderer, "resources/mieczyk.png", 100, 150);
   
    auto background_txt = std::make_shared<LTexture>();
    background_txt->loadFromFile(renderer, "resources/background.png");

    auto orb_border_text = std::make_shared<LTexture>();
    orb_border_text->loadFromFile(renderer, "resources/obramowka.png", ust.ORB_SIZE + 5, ust.ORB_SIZE + 5);

    auto hp_texture = std::make_shared<LTexture>();
    hp_texture->loadFromFile(renderer, "resources/kula_hp.png", 30 * ust.ORB_SIZE, ust.ORB_SIZE);

    auto mana_texture = std::make_shared<LTexture>();
    mana_texture->loadFromFile(renderer, "resources/kula_mana.png", 30 * ust.ORB_SIZE, ust.ORB_SIZE);

    std::cout << "Pomyslnie wczytano tekstury\n";

    // ---------------------------Object initialization-------------------------------------
    auto stachu = std::make_shared<Hero>(renderer, stachu_tekstura_idle, stachu_tekstura_run, stachu_tekstura_attack, kamera);
    //auto kask = std::make_shared<Renderable>(renderer, kask_text, kamera);
    //auto mieczyk = std::make_shared<Renderable>(renderer, mieczyk_text, kamera);
    auto background = std::make_shared<Tlo>(renderer, background_txt, kamera);

    auto hpOrb_border = std::make_shared<OrbBorder>(renderer, orb_border_text, 98, ust.SCREEN_HEIGHT - 204);
    auto manaOrb_border = std::make_shared<OrbBorder>(renderer, orb_border_text, 1300, ust.SCREEN_HEIGHT - 204);
    auto hpOrb = std::make_shared<Orb>(renderer, hp_texture, 100, ust.SCREEN_HEIGHT - 202);
    auto manaOrb = std::make_shared<Orb>(renderer, mana_texture, 1300, ust.SCREEN_HEIGHT - 202);

    auto testowy_diobel = std::make_shared<Enemy>(renderer, enemy_texture_idle, enemy_texture_run, enemy_texture_attack, kamera);

    std::cout << "Pomyslnie zainicjalizowano obiekty" << std::endl;

    // ---------------------------Creation of object layers--------------------------------
    GameObjectHandler objHandler;

    // drawing
    objHandler.subscribeBackground(background);
    objHandler.subscribePlayerLayer(stachu);
    objHandler.subscribeInterface(hpOrb);
    objHandler.subscribeInterface(manaOrb);
    objHandler.subscribeInterface(hpOrb_border);
    objHandler.subscribeInterface(manaOrb_border);
    objHandler.subscribePlayerLayer(testowy_diobel);

    // updates
    objHandler.subscribeUpdatable(stachu);
    objHandler.subscribeUpdatable(testowy_diobel);

    // events
    objHandler.subscribeEvents(stachu);

    // ---------------------------Additional initialization--------------------------------
    kamera->setFollow(stachu);
    testowy_diobel->setHero(stachu);
 
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

            for (auto& object : objHandler.getEventObjects())
            {
                object->handleEvent(e);
            }
        }

        // -----------------------------Movement------------------------------------------------
        end_time = SDL_GetPerformanceCounter();
        time_taken = ((double)(end_time - start_time) / (double)PerfCountFrequency) * 1000.0;
        //std::cout << 1.0 / (time_taken / 1000.0) <<  " "; // FPS
        accumulator += time_taken;
        start_time = end_time;

        while (accumulator >= ust.DT)
        {
            for (auto& object : objHandler.getUpdatableObjects())
            {
                object->update(ust.DT);
                if (object->destroy)
                {
                    objHandler.markForRemoval(std::make_shared <_GameObject>(dynamic_cast<_GameObject&>(*object)));
                }
            }
            accumulator -= ust.DT;
        }
        double alpha = accumulator / ust.DT;
        for (auto& object : objHandler.getUpdatableObjects())
        {
            object->interpolate(alpha);
        }

        //----------------------------Deletion of redundant objects------------------------
        while (true)
        {
            auto object = objHandler.popRemoval();
            if (object == nullptr) break;
            delete object.get();
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

        for (auto& element : objHandler.getInterfaceLayer())
        {
            element->render();
        }
      
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