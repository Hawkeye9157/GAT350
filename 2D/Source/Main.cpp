#include <SDL.h>
#include <iostream>
#include "Renderer.h"
#include "Framebuffer.h"

int main(int argc, char* argv[])
{
    Renderer* renderer = new Renderer;
    renderer->Initialize();

    renderer->CreateWindow(800, 600);
    
    Framebuffer framebuffer(*renderer,800, 600);

    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }
        }
        // clear screen
        //SDL_SetRenderDrawColor(renderer->m_renderer, 0, 0, 0, 0);
        //SDL_RenderClear(renderer->m_renderer);

        framebuffer.Clear(color_t{0,0,0,255});

        int x = rand() % framebuffer.m_width;
        int y = rand() % framebuffer.m_height;

        //for (int i = 0; i < 100; i++) {
        //    framebuffer.DrawPoint(x, y, color_t{ 255,255,255,255 });
        //}

        framebuffer.DrawRect(750, 10, 100, 100, color_t{ 255,255,255,255 });
        for (int i = 0; i < 100; i++) {
            framebuffer.DrawPoint(x,y,color_t{255,255,255,255});
        }
        //framebuffer.DrawPoint(10, 10, color_t{ 255,255,255,255 });

        framebuffer.Update();
        renderer->CopyFramebuffer(&framebuffer);

        // show screen
        SDL_RenderPresent(renderer->m_renderer);

    }
    return 0;
}