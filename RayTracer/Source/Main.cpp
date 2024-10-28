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
#include "Tracer.h"
#include "Scene.h"
#include "Sphere.h"
#include "Plane.h"

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

    SetBlendMode(BlendMode::Normal);
    Framebuffer framebuffer(*renderer, 800, 600);

    Camera camera{ 70.0f,800.0f / 600.0f };
    camera.SetView({ 0,0,-20 }, { 0,0,0 });
    Scene scene;

    std::shared_ptr<Material> mat = std::make_shared<Material>(color3_t{ 0,0.5f,0 });
    auto plane = std::make_unique<Plane>(glm::vec3{ 0,0,-20 }, glm::vec3{ 0,1,0 }, mat);
    //scene.AddObject(std::move(plane));

    std::shared_ptr<Material> material = std::make_shared<Material>(color3_t{ 0,0,1 });
    auto object = std::make_unique<Sphere>(glm::vec3{ 0,0,0 }, 5.0f, material);
    
    //scene.AddObject(std::move(object));

    std::shared_ptr<Material> gray = std::make_shared<Material>(color3_t{ 0.5f });
    std::shared_ptr<Material> red = std::make_shared<Material>(color3_t{ 1, 0, 0 });
    std::shared_ptr<Material> blue = std::make_shared<Material>(color3_t{ 0, 0, 1 });

    std::vector<std::shared_ptr<Material>> mats;
    mats.push_back(gray);
    mats.push_back(red);
    mats.push_back(blue);

    for (int i = 0; i < 5; i++) {
        auto object = std::make_unique<Sphere>(random(glm::vec3{ -10 }, glm::vec3{ 10 }), randomf(5.0f), mats.at(random(mats.size() - 1)));
        scene.AddObject(std::move(object));
    }

    
#pragma endregion
    bool quit = false;
    while (!quit)
    {
#pragma region Update
        time.Tick();
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
        framebuffer.Clear(ColorConvert(color4_t{ 1,1,1,1 }));

        scene.Render(framebuffer, camera);

        framebuffer.Update();
        renderer->CopyFramebuffer(&framebuffer);

        // show screen
        SDL_RenderPresent(renderer->m_renderer);
#pragma endregion
    }
    return 0;
}