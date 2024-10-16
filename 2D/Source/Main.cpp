#include <SDL.h>
#include <iostream>
#include "Renderer.h"
#include "Framebuffer.h"
#include "MathUtil.h"
#include "Image.h"
#include "PostProcess.h"
#include "Model.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>


int main(int argc, char* argv[])
{
    Renderer* renderer = new Renderer;
    renderer->Initialize();

    renderer->CreateWindow(800, 600);
    
    Framebuffer framebuffer(*renderer,800, 600);

    Image image;
    //image.Load("image.png");
    //image.Load("colors.png");
    //image.Load("cursed.png");
    image.Load("view.jpg");

    Image imageAlpha;
    //imageAlpha.Load("colors.png");
    imageAlpha.Load("cursed.png");
    
    

    vertices_t vertices = { {-5,5,0},{5,5,0},{-5,-5,0} };
    Model model(vertices, {255,0,0,255});
    
    SetBlendMode(BlendMode::Normal);
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
        framebuffer.Clear(color_t{128,128,128,255});

        
        int ticks = SDL_GetTicks();
        float time = ticks * .001f;
        float t = std::abs(std::sin(time));
#pragma region PostProcess
        //mouse input
        int mx, my;
        SDL_GetMouseState(&mx, &my);
        SetBlendMode(BlendMode::Alpha);
        framebuffer.DrawImage(10, 10, image);
        
        //PostProcess::Invert(framebuffer.m_buffer);
        PostProcess::Monochrome(framebuffer.m_buffer);
        //PostProcess::ColorBalance(framebuffer.m_buffer,50,30,20);
        PostProcess::Brightness(framebuffer.m_buffer, 50);
        //PostProcess::Threshold(framebuffer.m_buffer, 125);
        PostProcess::Noise(framebuffer.m_buffer, 15);
        //PostProcess::Posterization(framebuffer.m_buffer, 50);
        //PostProcess::Sharpen(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        SetBlendMode(BlendMode::Additive);
        framebuffer.DrawImage(mx, my, imageAlpha);

        PostProcess::Brightness(framebuffer.m_buffer, -125);
        PostProcess::Monochrome(framebuffer.m_buffer);
        //PostProcess::GaussianBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::BoxBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Sharpen(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Emboss(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Edge(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height,1);
#pragma endregion

        int r = 10;

        glm::mat4 modelMatrix = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate(modelMatrix, glm::vec3(340.0f, 240.0f, 0.0f));
        glm::mat4 scale = glm::scale(modelMatrix, glm::vec3(r, r, r));
        glm::mat4 rotate = glm::rotate(modelMatrix, glm::radians((time * 3) * 90), glm::vec3(1, 1, 1));

        modelMatrix = translate * scale * rotate;



        //model.Draw(framebuffer,modelMatrix);
       

        framebuffer.Update();
        renderer->CopyFramebuffer(&framebuffer);

        // show screen
        SDL_RenderPresent(renderer->m_renderer);
    }
    return 0;
}