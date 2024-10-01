#include <SDL.h>
#include <iostream>
#include "Renderer.h"

int main(int argc, char* argv[])
{
    Renderer* renderer = new Renderer;
    renderer->Initialize();

    renderer->CreateWindow(800, 600);
    
    while (true)
    {
        // clear screen
        SDL_SetRenderDrawColor(renderer->renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer->renderer);

        // show screen
        SDL_RenderPresent(renderer->renderer);
    }

    return 0;
}