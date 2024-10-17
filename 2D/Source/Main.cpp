#include <SDL.h>
#include <iostream>
#include "Renderer.h"
#include "Framebuffer.h"
#include "MathUtil.h"
#include "Image.h"
#include "PostProcess.h"
#include "Model.h"
#include "Transform.h"
#include "ETime.h"
#include "Input.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>


int main(int argc, char* argv[])
{
#pragma region Initialize
    Time time;

    Renderer* renderer = new Renderer;
    renderer->Initialize();
    renderer->CreateWindow(800, 600);

    Framebuffer framebuffer(*renderer, 800, 600);

    Input input;
    input.Initialize();
#pragma endregion
#pragma region Image_Init
    Image image;
    //image.Load("image.png");
    //image.Load("colors.png");
    //image.Load("cursed.png");
    image.Load("view.jpg");

    Image imageAlpha;
    imageAlpha.Load("colors.png");
    //imageAlpha.Load("cursed.png");
    SetBlendMode(BlendMode::Normal);
#pragma endregion
#pragma region Model_Init
    vertices_t vertices = { {-5,5,0},{5,5,0},{-5,-5,0} };
    Model model(vertices, { 255,0,0,255 });
    Transform transform{ {240,240,0},{0,0,90},{6,6,6} };
#pragma endregion


    bool quit = false;
    while (!quit)
    {
        time.Tick();
        input.Update();
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
        framebuffer.Clear(color_t{128,128,128,255});

        
#pragma region PostProcess
        //mouse input
        //int mx, my;
        //SDL_GetMouseState(&mx, &my);
        //SetBlendMode(BlendMode::Multiply);
        //framebuffer.DrawImage(10, 10, image);
        
        //PostProcess::Invert(framebuffer.m_buffer);
        //PostProcess::Monochrome(framebuffer.m_buffer);
        //PostProcess::ColorBalance(framebuffer.m_buffer,50,30,20);
        //PostProcess::Brightness(framebuffer.m_buffer, 50);
        //PostProcess::Threshold(framebuffer.m_buffer, 125);
        //PostProcess::Noise(framebuffer.m_buffer, 15);
        //PostProcess::Posterization(framebuffer.m_buffer, 50);
        //PostProcess::Sharpen(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //SetBlendMode(BlendMode::Alpha);
        //framebuffer.DrawImage(mx, my, imageAlpha);

        //PostProcess::Brightness(framebuffer.m_buffer, -125);
        //PostProcess::Monochrome(framebuffer.m_buffer);
        //PostProcess::GaussianBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::BoxBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Sharpen(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Emboss(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Edge(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height,1);
#pragma endregion
#pragma region Triangle_move
        glm::vec3 direction{ 0 };
        if (input.GetKeyDown(SDL_SCANCODE_RIGHT)) {direction.x = 1;}
        if (input.GetKeyDown(SDL_SCANCODE_LEFT)) {direction.x = -1;}
        if (input.GetKeyDown(SDL_SCANCODE_UP)) {direction.y = -1;}
        if (input.GetKeyDown(SDL_SCANCODE_DOWN)) {direction.y = 1;}
        if (input.GetKeyDown(SDL_SCANCODE_K)) {direction.z = 1;}
        if (input.GetKeyDown(SDL_SCANCODE_L)) {direction.z = -1;}
        transform.position += direction * 100.0f * time.GetDeltaTime();
        transform.rotation.z += 90 * time.GetDeltaTime();
        transform.rotation.y += 90 * time.GetDeltaTime();
        transform.rotation.x += 90 * time.GetDeltaTime();
        model.Draw(framebuffer,transform.GetMatrix());
#pragma endregion
       

        framebuffer.Update();
        renderer->CopyFramebuffer(&framebuffer);

        // show screen
        SDL_RenderPresent(renderer->m_renderer);
    }
    return 0;
}