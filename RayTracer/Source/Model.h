#pragma once
#include "Color.h"
#include "SceneObject.h"

#include <glm/glm.hpp>
#include <vector>
#include <string>

using vertex_t = glm::vec3;
using vertices_t = std::vector<vertex_t>;

class Model : public SceneObject{
public:
	Model(std::shared_ptr<Material> mat) : SceneObject{ mat } {}
	Model(const vertices_t& vertices, std::shared_ptr<Material> mat) : SceneObject{ mat }, m_vertices{ vertices } {}
	//Model(const vertices_t& vertices, const color_t& color) : m_vertices{ vertices }, m_color{ color } {}

	bool Load(const std::string& filename);
	
	bool Hit(const ray_t& ray,raycastHit_t& raycastHit,float min, float max) override;

private:
	vertices_t m_vertices;
	
};