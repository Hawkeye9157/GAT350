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
#include "Material.h"
#include "Triangle.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <SDL.h>
#include <iostream>
#include <memory>

void InitScene(Scene& scene);
static void InitScene01(Scene& scene, Camera& camera);


int main(int argc, char* argv[])
{
    srand((unsigned int)time(NULL));
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
   InitScene01(scene,camera);

    scene.Update();
    scene.Render(framebuffer, camera, 200, 200);
    framebuffer.Update();
    
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
        //framebuffer.Clear(ColorConvert(color4_t{ 1,1,1,1 }));

        

       //framebuffer.Update();
        renderer->CopyFramebuffer(&framebuffer);

        // show screen
        SDL_RenderPresent(renderer->m_renderer);
#pragma endregion
    }
    return 0;
}

void InitScene(Scene& scene) {

    //scene.SetSky(HSVtoRGB(240, 1, 0.5f), HSVtoRGB(240, 1, 1));
    std::shared_ptr<Material> mat = std::make_shared<Lambertian>(color3_t{ 0.5f,0.5f,0.5f });
    auto plane = std::make_unique<Plane>(Transform{ glm::vec3{0,0,0},glm::vec3{0,0,0},glm::vec3{1,1,1} }, mat);
    scene.AddObject(std::move(plane));

    //std::shared_ptr<Material> material = std::make_shared<Lambertian>(color3_t{ 0,0,1 });
    //auto object = std::make_unique<Sphere>(glm::vec3{ 0,0,0 }, 5.0f, material);

    //scene.AddObject(std::move(object));

    //std::shared_ptr<Material> gray = std::make_shared<Dielectric>(color3_t{ 0.5f }, 1.333f);
    std::shared_ptr<Material> red = std::make_shared<Emissive>(color3_t{ 1, 0, 0 }, 1.5f);
    //std::shared_ptr<Material> blue = std::make_shared<Metal>(color3_t{ 0, 0, 1 }, 0.7f);
    //std::shared_ptr<Material> something = std::make_shared<Emissive>(color3_t{ randomf(1), randomf(1), randomf(1) }, 1.75f);
    //std::shared_ptr<Material> something2 = std::make_shared<Metal>(color3_t{ randomf(1), randomf(1), randomf(1) }, 1.75f);
    //std::shared_ptr<Material> something3 = std::make_shared<Dielectric>(color3_t{ randomf(1), randomf(1), randomf(1) }, 1.0f);
    //std::shared_ptr<Material> something4 = std::make_shared<Emissive>(color3_t{ randomf(1), randomf(1), randomf(1) }, 1.75f);

    //std::vector<std::shared_ptr<Material>> mats;
    //mats.push_back(gray);
    //mats.push_back(red);
    //mats.push_back(blue);
    //mats.push_back(something);
    //mats.push_back(something2);
    //mats.push_back(something3);
    //mats.push_back(something4);

    //for (int i = 0; i < 20; i++) {
      //  auto object = std::make_unique<Sphere>(Transform{ random(glm::vec3{-10,-10,-10},glm::vec3{10,10,10}),glm::vec3{0,0,0},glm::vec3{1,1,1} }, 2.0f, mats.at(random(0, mats.size())));
        //scene.AddObject(std::move(object));
    //}
    //auto triangle = std::make_unique<Triangle>(glm::vec3{ -2,2,0 }, glm::vec3{ 0,4,0 }, glm::vec3{ 2,2,0 }, red);
    auto model = std::make_unique<Model>(Transform{ glm::vec3{0,0,0},glm::vec3{0,0,0},glm::vec3{2} }, std::make_shared<Emissive>(HSVtoRGB(randomf(0,360),randomf(0,1),randomf(0,1)),1.3f));
    model.get()->Load("Models/suzanne.obj");
    scene.AddObject(std::move(model));
    //scene.AddObject(std::move(triangle));
}
static void InitScene01(Scene& scene, Camera& camera)
{
    camera.SetFOV(20.0f);
    camera.SetView({ 13, 2, 3 }, { 0, 0, 0 });

   // auto ground_material = std::make_shared<Lambertian>(color3_t(0.5f));
    //scene.AddObject(std::make_unique<Plane>(Transform{ glm::vec3{ 0 } }, ground_material));

    std::shared_ptr<Material> mat = std::make_shared<Lambertian>(color3_t{ 0.5f,0.5f,0.5f });
    auto plane = std::make_unique<Plane>(Transform{ glm::vec3{0} }, mat);
    scene.AddObject(std::move(plane));

    
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = randomf();
            glm::vec3 center(a + 0.9 * randomf(), 0.2, b + 0.9 * randomf());

            if ((center - glm::vec3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = HSVtoRGB(randomf(0, 360), 1.0f, 1.0f);
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    scene.AddObject(std::make_unique<Sphere>(Transform{ center }, 0.2f, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = HSVtoRGB(randomf(0, 360), 1.0f, 1.0f);
                    auto fuzz = randomf(0.0f, 0.5f);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    scene.AddObject(std::make_unique<Sphere>(Transform{ center }, 0.2f, sphere_material));
                }
                else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(color3_t{ 1 }, 1.5f);
                    scene.AddObject(std::make_unique<Sphere>(Transform{ center }, 0.2f, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(color3_t{ 1 }, 1.5f);
    scene.AddObject(std::make_unique<Sphere>(Transform{ glm::vec3{ 0, 1, 0 } }, 1.0f, material1));

    auto material2 = std::make_shared<Lambertian>(color3_t(0.4f, 0.2f, 0.1f));
    scene.AddObject(std::make_unique<Sphere>(Transform{ glm::vec3{ -4, 1, 0 } }, 1.0f, material2));

    auto material3 = std::make_shared<Metal>(color3_t(0.7f, 0.6f, 0.5f), 0.0f);
    scene.AddObject(std::make_unique<Sphere>(Transform{ glm::vec3{ 4, 1, 0 } }, 1.0f, material3));
    
}