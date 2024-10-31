#include "Scene.h"
#include "Framebuffer.h"
#include "Ray.h"
#include "Camera.h"
#include "Tracer.h"
#include "Random.h"
#include <iostream>

void Scene::Render(Framebuffer& framebuffer, const Camera& camera,int samples,int depth)
{
	for (int y = 0; y < framebuffer.GetHeight(); y++) {
		for (int x = 0; x < framebuffer.GetWidth(); x++) {
			color3_t color{ 0 };
			for (int i = 0; i < samples; i++) {
				glm::vec2 pixel{ x,y };
				pixel += glm::vec2{ randomf(),randomf() };

				glm::vec2 point = pixel / glm::vec2{ framebuffer.m_width,framebuffer.m_height };
				point.y = 1 - point.y;

				ray_t ray = camera.GetRay(point);
				color3_t colors = Tracer::Trace(*this, ray, 0.001f, 100.0f, depth);
				color += colors;
			}
			color = color / (float)samples;
			framebuffer.DrawPoint(x, y, ColorConvert(color));
		}
		std::cout << "y: " << y << std::endl;
	}
}
