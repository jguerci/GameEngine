#include "Mesh.h"

#include <iostream>
#include <cstddef>
#include <sstream>

Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

void Mesh::Init(vector<Vertex> vertices, vector<GLuint> indices, vector<GLuint> textures)
{
	vertices_ = vertices;
	indices_ = indices;
	textures_ = textures;

	for (auto i = 0; i < indices_.size(); i += 3)
	{
		int in1 = indices_[i + 0];
		int in2 = indices_[i + 1];
		int in3 = indices_[i + 2];

		glm::vec3 p1 = vertices[in1].position;
		glm::vec3 p2 = vertices[in2].position;
		glm::vec3 p3 = vertices[in3].position;

		glm::vec3 v1 = p2 - p1;
		glm::vec3 v2 = p3 - p1;
		glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

		vertices_[in1].normal = glm::normalize(vertices_[in1].normal + normal);
		vertices_[in2].normal = glm::normalize(vertices_[in2].normal + normal);
		vertices_[in3].normal = glm::normalize(vertices_[in3].normal + normal);
	}

	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	glGenBuffers(1, &ebo_);

	glBindVertexArray(vao_);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices_.size(), &vertices_[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices_.size(), &indices_[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Mesh::Draw(Shader shader)
{
	glBindVertexArray(vao_);
	glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	for (GLuint i = 0; i < textures_.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}