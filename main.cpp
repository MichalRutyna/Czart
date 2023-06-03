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
    //przezroczystosc - stachu_tekstura->setAlpha(255);

    auto stachu = std::make_shared<PlayerMovable>(renderer, stachu_tekstura, kamera);
    kamera->setFollow(stachu);
    
    // -----------------------------------------------------------------------------------
    auto kask_text = std::make_shared<LTexture>();
    kask_text->loadFromFile(renderer, "resources/czapka.png", 350, 35);
    auto kask = std::make_shared<Renderable>(renderer, kask_text, kamera);
    kask->change_center(stachu->getPosX()+25+stachu_tekstura->width()/2, stachu->getPosY()+10+stachu_tekstura->height()/2);

    auto mieczyk_text = std::make_shared<LTexture>();
    mieczyk_text->loadFromFile(renderer, "resources/mieczyk.png", 100, 150);
    auto mieczyk = std::make_shared<Renderable>(renderer, mieczyk_text, kamera);
   
    // -----------------------------------------------------------------------------------
    auto background_txt = std::make_shared<LTexture>();
    background_txt->loadFromFile(renderer, "resources/background.png");
    auto background = std::make_shared<Renderable>(renderer, background_txt, kamera);
    // -----------------------------------------------------------------------------------
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
    // -----------------------------------------------------------------------------------
    std::vector<std::shared_ptr<Renderable>> obiektyProgramu;
    obiektyProgramu.push_back(stachu);
    obiektyProgramu.push_back(background);

    // -----------------------------------------------------------------------------------
 
    std::vector<std::shared_ptr<Renderable>> movableObjects;

    // -----------------------------------------------------------------------------------
    auto frame_timer = std::make_shared<LTimer>();
    uint64_t accumulator = 0;
    // -----------------------------------------------------------------------------------

    int hp_frame = 0;
    int i = 0;
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
        
        currentClip->y = 0 + i * 20;
        currentClip->h = 150 - i * 20;
        
        hp_texture.render(renderer, 100, ust.SCREEN_HEIGHT - 202 + i*20, currentClip);
        mana_texture.render(renderer, 1300, ust.SCREEN_HEIGHT - 202 + i*20, currentClip);
        hp_frame++;
        if (hp_frame/5 >= 30) hp_frame = 0;
        orb_border->render(98, ust.SCREEN_HEIGHT - 204); // hp
        orb_border->render(1300, ust.SCREEN_HEIGHT - 204); // mana

        SDL_RenderPresent(renderer.get()); //update
        

        // -----------------------------------------------------------------------------------
        
       // kask->change_angle(i);
       // stachu->change_angle(i);
        //i+=0.1;
    }
    close();
    return 0;
}