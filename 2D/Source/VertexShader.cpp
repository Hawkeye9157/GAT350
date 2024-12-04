#include "VertexShader.h"
#include "Shader.h"




void VertexShader::Process(const vertex_t& ivertex, vertex_output_t& overtex)
{
	glm::mat4 mvp = Shader::uniforms.proj * Shader::uniforms.view * Shader::uniforms.model;
	overtex.position = mvp * glm::vec4{ ivertex.position,1 };
	glm::mat4 mv = Shader::uniforms.view * Shader::uniforms.model;
	overtex.normal = glm::normalize(glm::mat3{ mv } * ivertex.normal);

	glm::vec3 light_position{ 3,3,-3 };
	glm::vec3 vp = mv * glm::vec4{ ivertex.position,1 };
	glm::vec3 light_dir = glm::normalize(light_position - vp);

	float intensity = std::max(0.0f,glm::dot(light_dir, overtex.normal));
	
	
	//lighting
	if (Shader::uniforms.light.directional) {
		Shader::uniforms.light.direction = glm::vec4{ Shader::uniforms.light.direction,1 } *Shader::uniforms.view;
		Shader::uniforms.light.direction - glm::normalize(-Shader::uniforms.light.direction);
		intensity = std::max(0.0f,glm::dot(Shader::uniforms.light.direction, ivertex.normal));
	}
	else { //point lighting
		Shader::uniforms.light.position = glm::vec4{ Shader::uniforms.light.position, 1} *Shader::uniforms.view;
		glm::vec3 dv = { Shader::uniforms.light.position.x - overtex.position.x ,Shader::uniforms.light.position.y - overtex.position.y
			,Shader::uniforms.light.position.z - overtex.position.z };
		Shader::uniforms.light.direction = glm::normalize(Shader::uniforms.light.direction);
		intensity = std::max(0.0f, glm::dot(Shader::uniforms.light.direction, ivertex.normal));
	}


	color3_t diffuse = Shader::uniforms.light.color * intensity;

	overtex.color = Shader::uniforms.ambient + diffuse;
}
