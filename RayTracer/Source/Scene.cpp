#include "Scene.h"
#include "Framebuffer.h"
#include "Ray.h"
#include "Camera.h"
#include "Tracer.h"
#include <iostream>

void Scene::Render(Framebuffer& framebuffer, const Camera& camera)
{
	for (int y = 0; y < framebuffer.GetHeight(); y++) {
		for (int x = 0; x < framebuffer.GetWidth(); x++) {
			glm::vec2 pixel{ x,y };
			glm::vec2 point = pixel / glm::vec2{ framebuffer.GetWidth(),framebuffer.GetHeight()};
			point.y = 1 - point.y;
			ray_t ray = camera.GetRay(point);
			color3_t color = Tracer::Trace(*this, ray,0.001f,100.0f);
			//color4_t color2 = { 0.75f,0.25f,0.5f,1 };
			framebuffer.DrawPoint(x, y, ColorConvert(color));
		}
		std::cout << "y: " << y << std::endl;
	}
}
