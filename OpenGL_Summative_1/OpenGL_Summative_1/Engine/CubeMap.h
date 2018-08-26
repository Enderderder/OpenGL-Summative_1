#pragma once

// Global Include
#include "Utility.h"

// Forward Declare
class CMesh;
class CCamera;

class CCubeMap
{
public:
	CCubeMap();
	~CCubeMap();

	void RenderCubeMap(CCamera* _camera);

private:
	
	GLuint m_programID;
	GLuint m_texture;
	CMesh* m_cubemapMesh;

};

