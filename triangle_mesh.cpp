#include "triangle_mesh.h"

TriangleMesh::TriangleMesh()
{
	std::vector<float> data = {
		 -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		 -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		 1.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f
	};
	vertex_count = 6;
	std::vector<int> index = { 0, 1, 2, 2, 1, 3 };

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//Vertex Buffer Object
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(float), data.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)12);
	glEnableVertexAttribArray(1);

	//Element Buffer Object
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(int), index.data(), GL_STATIC_DRAW);


}

void TriangleMesh::draw()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, 0);
}

TriangleMesh::~TriangleMesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
