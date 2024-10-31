#pragma once
#include "SceneObject.h"
#include <vector>
#include <memory>

class Scene {
public:
	Scene() = default;

	void AddObject(std::unique_ptr<class SceneObject> object) { m_objects.push_back(std::move(object)); }
	void Render(class Framebuffer& framebuffer, const class Camera& camera,int samples = 10,int depth = 5);

	friend class Tracer;
	
private:
	std::vector < std::unique_ptr<class SceneObject>> m_objects;
};