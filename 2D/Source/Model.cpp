#include "Model.h"
#include "Framebuffer.h"
#include "Camera.h"

void Model::Draw(Framebuffer& framebuffer, const glm::mat4& model, const Camera& camera)
{
	for (int i = 0; i < m_vertices.size(); i += 3) {
		//convert
		vertex_t p1 = model * glm::vec4{ m_vertices[i],1 };
		vertex_t p2 = model * glm::vec4{ m_vertices[i + 1],1 };
		vertex_t p3 = model * glm::vec4{ m_vertices[i + 2],1 };

		p1 = camera.ModelToView(p1);
		p2 = camera.ModelToView(p2);
		p3 = camera.ModelToView(p3);

		glm::ivec2 s1 = camera.ToScreen(p1);
		glm::ivec2 s2 = camera.ToScreen(p2);
		glm::ivec2 s3 = camera.ToScreen(p3);

		framebuffer.DrawTriangle(s1.x, s1.y, s2.x, s2.y, s3.x, s3.y, m_color);
	}
}
