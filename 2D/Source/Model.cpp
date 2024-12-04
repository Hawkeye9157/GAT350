#include "Model.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool Model::Load(const std::string& filename)
{
	std::ifstream stream(filename);
	if (!stream.is_open()) {
		std::cerr << "Error opening ifstream" << std::endl;
		return false;
	}
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::string line;
	while (std::getline(stream, line)) {
		//read in vertex positions
		if (line.substr(0,2) == "v ") {
			std::istringstream sstream{line.substr(2)};
			glm::vec3 position;
			sstream >> position.x;
			sstream >> position.y;
			sstream >> position.z;
			vertices.push_back(position);
		}
		//read in vertex normals
		else if (line.substr(0, 3) == "vn ") {
			std::istringstream sstream{ line.substr(3) };
			glm::vec3 normal;
			sstream >> normal.y;
			sstream >> normal.z;
			sstream >> normal.x;
			normals.push_back(normal);
		}
		else if (line.substr(0,2) == "f ") {
			std::istringstream sstream{ line.substr(2) };
			std::string str;
			while (std::getline(sstream,str,' ')) {
				std::istringstream sstream(str);
				std::string indexString;

				size_t i = 0;
				unsigned int index[3] = { 0,0,0 };
				while (std::getline(sstream,indexString,'/')) {
					if (!indexString.empty()) {
						std::istringstream indexStream{ indexString };
						//stream indexstream into index[i]
						indexStream >> index[i];
					}
					i++;
				}
				if (index[0] != 0) {
					vertex_t vertex;
					vertex.position = vertices[index[0] - 1];
					vertex.normal = (index[1]) ? normals[index[1] - 1] : glm::vec3{ 1 };
					
					m_vertices.push_back(vertex);
				}
			}
		}
	}
	stream.close();
	return true;
}

void Model::DrawModel(Framebuffer& framebuffer,const Camera& camera,color_t color) //fix
{
	/*
	for (int i = 0; i < m_vertices.size() - 2; i += 3) {
		//convert
		vertex_t p1 = glm::vec4{ m_vertices[i],1 };
		vertex_t p2 = glm::vec4{ m_vertices[i + 1],1 };
		vertex_t p3 = glm::vec4{ m_vertices[i + 2],1 };
			p1 = camera.ModelToView(p1);
			p2 = camera.ModelToView(p2);
			p3 = camera.ModelToView(p3);
			
			glm::ivec2 s1 = camera.ToScreen(p1);
			glm::ivec2 s2 = camera.ToScreen(p2);
			glm::ivec2 s3 = camera.ToScreen(p3);
			
			
			framebuffer.DrawTriangle((int)s1.x, (int)s1.y, (int)s2.x, (int)s2.y,(int)s3.x,(int)s3.y, color);
	}
	*/
}

void Model::Draw()
{
	Shader::Draw(m_vertices);
	
}
