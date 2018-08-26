#pragma once

// Inherited Include
#include "Mesh.h"


class CCubemapMesh : public CMesh
{
public:
	CCubemapMesh();
	~CCubemapMesh();

private:

	virtual void RenderMesh() override;

};