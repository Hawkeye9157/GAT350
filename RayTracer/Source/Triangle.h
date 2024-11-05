#pragma once
#include "SceneObject.h"

class Triangle : public SceneObject {
public:
	Triangle(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, std::shared_ptr<Material> mat) : SceneObject{mat},
		m_local_v1{ v1 }, m_local_v2{ v2 }, m_local_v3{v3} {}
	Triangle(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, std::shared_ptr<Material> mat, const Transform& transform) :
		SceneObject{ transform,mat },m_local_v1{ v1 }, m_local_v2{ v2 }, m_local_v3{ v3 } {}

	bool Hit(const ray_t& ray,raycastHit_t& raycastHit,float minDistance, float maxDistance) override;
	static bool Raycast(const ray_t& ray, const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, float min, float max, float& t);
	void Update() override;

private:
	glm::vec3 m_v1{ 0 };
	glm::vec3 m_v2{ 0 };
	glm::vec3 m_v3{ 0 };

	glm::vec3 m_local_v1{ 0 };
	glm::vec3 m_local_v2{ 0 };
	glm::vec3 m_local_v3{ 0 };
};