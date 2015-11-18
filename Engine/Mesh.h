#pragma once

#include <GL\glew.h>
#include <vector>

#include "Vertex.h"
#include "Shader.h"

using namespace std;

class Mesh
{
public:
	Mesh();
	~Mesh();

	void Init(vector<Vertex> vertices, vector<GLuint> indices, vector<GLuint> textures);
	void Draw(Shader shader);
private:
	GLuint vao_ = 0;
	GLuint vbo_ = 0;
	GLuint ebo_ = 0;

	vector<Vertex> vertices_;
	vector<GLuint> indices_;
	vector<GLuint> textures_;
};

