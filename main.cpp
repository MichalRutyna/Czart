// ConsoleApplication1.cpp : Ten plik zawiera funkcjê „main”. W nim rozpoczyna siê i koñczy wykonywanie programu.
//

#include <iostream>
#include <SDL.h>
#include <vector>

using namespace std;

class Hero {
private:
    const int WIDTH;
    const int HEIGHT;
    const string NAME;

    // Bardziej przyœpiesznie
    const int VELOCITY;

    // Faktyczne pozycje
    int memberPosX, memberPosY;

    // Aktualna prêdkoœæ
    int memberVelX, memberVelY;

public:
    Hero() : WIDTH(20), HEIGHT(30), NAME("Stachu Jones"), VELOCITY(10) {}

    //void handleEvent(SDL_Event% e);

    void move();

    void render();
};

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
    SDL_Window* window = NULL;

    SDL_Surface* screenSurface = NULL;

    SDL_Surface* gHelloWorld = NULL; // OBRAZEK

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Eroor: %s\n", SDL_GetError());
    }
    else
    {
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface(window);

            //Fill the surface white
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

            //Update the surface
            SDL_UpdateWindowSurface(window);

            //Hack to get window to stay up
            SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
        }
    }
    gHelloWorld = SDL_LoadBMP("hello_world.bmp");
    if (gHelloWorld == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
    }
    //Destroy window
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;
    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();
    std::cout << "CYCE";
    return 0;
}