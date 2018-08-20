#pragma once

// Global Include
#include "Utility.h"

// Derive Include
#include "Component.h"

// Forward Declare
class CMesh;
class CCamera;

class CMeshComponent : public CComponent
{
public:
	CMeshComponent();
	~CMeshComponent();

	void SetMesh(CMesh* _mesh);
	void SetTexture(GLuint _texture);

	void RenderMesh(CCamera* _camera);

private:

	CMesh * m_mesh;
	GLuint m_texture;

};

