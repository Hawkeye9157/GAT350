#pragma once
#include "SceneObject.h"
#include "glm/glm.hpp"
#include "Ray.h"

class Sphere : public SceneObject {
public:
	Sphere() = default;
	Sphere(const Transform& trans, float radius, std::shared_ptr<Material> mat) : SceneObject(trans, mat), radius{ radius } {}
	Sphere(const glm::vec3& center, float radius, std::shared_ptr<Material> material) : SceneObject(material), m_center{ center }, radius{ radius } {}

	// Inherited via SceneObject
	bool Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance) override;
	static bool Raycast(const ray_t& ray, const glm::vec3& center, float radius, float min, float max,float& t);

private:
	glm::vec3 m_center{ 0 };
	float radius{ 0 };

};