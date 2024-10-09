#include <SDL.h>
#include <iostream>
#include "Renderer.h"
#include "Framebuffer.h"
#include "MathUtil.h"
#include "Image.h"

int main(int argc, char* argv[])
{
    Renderer* renderer = new Renderer;
    renderer->Initialize();

    renderer->CreateWindow(800, 600);
    
    Framebuffer framebuffer(*renderer,800, 600);

    Image image;
    image.Load("image.png");

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

        int x1 = rand() % framebuffer.m_width;
        int x2 = rand() % framebuffer.m_width;
        int x3 = rand() % framebuffer.m_width;
        int y1 = rand() % framebuffer.m_height;
        int y2 = rand() % framebuffer.m_height;
        int y3 = rand() % framebuffer.m_height;
        int mx, my;
        SDL_GetMouseState(&mx, &my);
     
       //framebuffer.DrawLine(x, y, x2, y2, color_t{ 255,0,0,255 });
       //framebuffer.DrawTriangle(x + 3, y + 30, x2 - 40, y2 + 25,x3,y3, color_t{ 0,0,255,255 });
       //framebuffer.DrawCircle(400, 300, 100, color_t{ 255,255,255,255 });
       //framebuffer.DrawLinearCurve(100, 100, 200, 200, color_t{ 255,0,255,255 });
       //framebuffer.DrawQuadraticCurve(100, 200, 200, 100, 300, 200, color_t{ 255,255,0,255 });
       framebuffer.DrawCubicCurve(100, 200, 100, 100, 200, 100, 200, 200, color_t{ 0,255,255,255 });

       int ticks = SDL_GetTicks();
       float time = ticks * 0.01f;
       int x, y;
       float t = std::abs(std::sin(time));
       CubicPoint(100, 200, 100, 100, 200, 100, 200, 200, t, x, y);
       framebuffer.DrawRect(x - 20,y - 20,40,40,color_t{255,255,255,255});

       framebuffer.DrawImage(400, 300, image);

        framebuffer.Update();
        renderer->CopyFramebuffer(&framebuffer);

        // show screen
        SDL_RenderPresent(renderer->m_renderer);
    }
    return 0;
}