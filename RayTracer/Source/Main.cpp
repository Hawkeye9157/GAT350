#include "Renderer.h"
#include "Framebuffer.h"
#include "MathUtil.h"
#include "Image.h"
#include "PostProcess.h"
#include "Model.h"
#include "Transform.h"
#include "ETime.h"
#include "Input.h"
#include "Camera.h"
#include "Actor.h"
#include "Random.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <SDL.h>
#include <iostream>
#include <memory>

int main(int argc, char* argv[])
{
#pragma region Initialize

    Time time;

    Renderer* renderer = new Renderer;
    renderer->Initialize();
    renderer->CreateWindow(800, 600);

    Framebuffer framebuffer(*renderer, 800, 600);
    Camera camera(800, 600);
    camera.SetView(glm::vec3{ 0,0,-5 }, glm::vec3{ 0 });
    camera.Setprojection(90.0f, 800.0f / 600.0f, 0.1f, 200.0f);
    Transform cameraTransform{ {0,0,-50} };
    cameraTransform.rotation = { 90,90,90 };

    Input input;
    input.Initialize();
    input.Update();
#pragma endregion
#pragma region Image_Init
    Image image;
    image.Load("image.png");
    //image.Load("colors.png");
    //image.Load("cursed.png");
    //image.Load("view.jpg");

    Image imageAlpha;
    imageAlpha.Load("colors.png");
    //imageAlpha.Load("cursed.png");
    //SetBlendMode(BlendMode::Normal);
#pragma endregion
#pragma region Model_Init
    std::shared_ptr<Model> model = std::make_shared<Model>();
    //model->Load("sword.obj");
    model->Load("skull.obj");

    std::vector<std::unique_ptr<Actor>> actors;

    for (int i = 0; i < 1; i++) {
        //Transform transform{ {randomf(-10.0f,10.0f),randomf(-10.0f,10.0f),randomf(-10.0f,10.0f)},{0,0,15},{1,1,1}};
        Transform transform{ {100,100,10},{0,0,15},{1,1,1} };
        std::unique_ptr<Actor> actor = std::make_unique<Actor>(transform, model);
        actors.push_back(std::move(actor));
        
    }
#pragma endregion
    bool quit = false;
    while (!quit)
    {
#pragma region Update
        time.Tick();
        input.Update();
#pragma endregion
#pragma region SDL_EVENT
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }
        }
#pragma endregion
#pragma region Draw
        // clear screen
        framebuffer.Clear(color_t{ 128,128,128,255 });



#pragma region PostProcess
        //mouse input
        //int mx, my;
        //SDL_GetMouseState(&mx, &my);
        SetBlendMode(BlendMode::Normal);
        //framebuffer.DrawImage(10, 10, image);

        //PostProcess::Invert(framebuffer.m_buffer);
        //PostProcess::Monochrome(framebuffer.m_buffer);
        //PostProcess::ColorBalance(framebuffer.m_buffer,50,30,20);
        //PostProcess::Brightness(framebuffer.m_buffer, 50);
        //PostProcess::Threshold(framebuffer.m_buffer, 125);
        //PostProcess::Noise(framebuffer.m_buffer, 15);
        //PostProcess::Posterization(framebuffer.m_buffer, 50);
        //PostProcess::Sharpen(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //SetBlendMode(BlendMode::Additive);
        //framebuffer.DrawImage(100, 100, imageAlpha);

        //PostProcess::Brightness(framebuffer.m_buffer, -125);
        //PostProcess::Monochrome(framebuffer.m_buffer);
        //PostProcess::GaussianBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::BoxBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Sharpen(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Emboss(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Edge(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height,1);
#pragma endregion
#pragma region Triangle_move
        if (input.GetMouseButtonDown(2)) {
            input.SetRelativeMode(true);

            glm::vec3 direction{ 0 };
            if (input.GetKeyDown(SDL_SCANCODE_D)) { direction.x = 1; }
            if (input.GetKeyDown(SDL_SCANCODE_A)) { direction.x = -1; }
            if (input.GetKeyDown(SDL_SCANCODE_W)) { direction.y = -1; }
            if (input.GetKeyDown(SDL_SCANCODE_S)) { direction.y = 1; }
            if (input.GetKeyDown(SDL_SCANCODE_K)) { direction.z = -1; }
            if (input.GetKeyDown(SDL_SCANCODE_L)) { direction.z = 1; }

            cameraTransform.rotation.y += input.GetMousePositionDelta().x * 0.25;
            cameraTransform.rotation.x += input.GetMousePositionDelta().y * 0.25;

            glm::vec3 offset = cameraTransform.GetMatrix() * glm::vec4{ direction,0 };

            cameraTransform.position += offset * 70.0f * time.GetDeltaTime();
        }
        else {
            input.SetRelativeMode(false);
        }

        camera.SetView(cameraTransform.position, cameraTransform.position + cameraTransform.GetForward());
        //camera.SetView(cameraTransform.position, cameraTransform.position + glm::vec3{0,0,1});

        for (auto& actor : actors) {
            actor->SetColor({ (uint8_t)randomf(255.0f),(uint8_t)randomf(255.0f),(uint8_t)randomf(255.0f),255 });
            actor->Draw(framebuffer, camera);
        }
#pragma endregion


        framebuffer.Update();
        renderer->CopyFramebuffer(&framebuffer);

        // show screen
        SDL_RenderPresent(renderer->m_renderer);
#pragma endregion
    }
    return 0;
}