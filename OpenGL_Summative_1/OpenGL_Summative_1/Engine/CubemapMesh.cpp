

// This Include
#include "CubemapMesh.h"

CCubemapMesh::CCubemapMesh()
{
	GLfloat cubeVertices[] = {

		// Right Face
		 1.0f,  1.0f,  1.0f,    // 0
		 1.0f,  1.0f, -1.0f,    // 1
		 1.0f, -1.0f, -1.0f,	// 2
		 1.0f, -1.0f,  1.0f,    // 3

		// Left Face
		-1.0f,  1.0f, -1.0f,	// 4
		-1.0f,  1.0f,  1.0f,	// 5
		-1.0f, -1.0f,  1.0f,	// 6
		-1.0f, -1.0f, -1.0f,	// 7

		// Top Face
		-1.0f,  1.0f, -1.0f,	// 8
		 1.0f,  1.0f, -1.0f,    // 9
		 1.0f,  1.0f,  1.0f,    // 10
		-1.0f,  1.0f,  1.0f,    // 11

		// Bottom Face
		-1.0f, -1.0f,  1.0f,    // 12
		 1.0f, -1.0f,  1.0f,    // 13
		 1.0f, -1.0f, -1.0f,    // 14
		-1.0f, -1.0f, -1.0f,    // 15

		// Back Face
		 1.0f,  1.0f, -1.0f,    // 16
		-1.0f,  1.0f, -1.0f,    // 17
		-1.0f, -1.0f, -1.0f,	// 18
		 1.0f, -1.0f, -1.0f,    // 19

		// Front Face
		-1.0f,  1.0f,  1.0f,	// 20
		 1.0f,  1.0f,  1.0f,	// 21
		 1.0f, -1.0f,  1.0f,	// 22
		-1.0f, -1.0f,  1.0f,	// 23
	};

	GLuint cubeIndices[] = {

		// Right Face	// Bottom Face
		0, 1, 2,		12, 13, 14,
		0, 2, 3,		12, 14, 15,

		// Left Face	// Back Face
		4, 5, 6,		16, 17, 18,
		4, 6, 7,		16, 18, 19,

		// Top Face		// Front Face
		8, 9, 10,		20, 21, 22,
		8, 10, 11,		20, 22, 23,
	};

	// Bind VBO and EBO and store the VAO
	GLuint VBO, EBO;

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
}

CCubemapMesh::~CCubemapMesh()
{}

void CCubemapMesh::RenderMesh()
{
	// Bind the VAO and draw the cube map
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	// unBind
	glBindVertexArray(0);
}
