#pragma once
#include "Material.h"
#include "Ray.h"
#include "Transform.h"
#include <memory>
class SceneObject {
public:
	SceneObject(std::shared_ptr<Material> material) : m_material{material} {}
	SceneObject(const Transform& transform, std::shared_ptr<Material> material ) : m_material{ material }, m_transform{transform} {}

	virtual bool Hit(const ray_t& ray, raycastHit_t& raycastHit,float minDistance, float maxDistance) = 0;
	virtual void Update() {}

	std::shared_ptr<Material> GetMaterial() { return m_material; }
	Transform& GetTransform() { return m_transform; }
	const Transform& GetTransform() const { return m_transform; }


protected:
	std::shared_ptr<Material> m_material;
	Transform m_transform;
};