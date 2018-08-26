
// This Include
#include "CubeMap.h"

// Engine Include
#include "AssetMgr.h"
#include "Camera.h"
#include "Mesh.h"

CCubeMap::CCubeMap()
{
	m_cubemapMesh = CAssetMgr::GetInstance()->GetMesh("DefaultCubemapMesh");
	m_programID = CAssetMgr::GetInstance()->GetProgramID("CubemapProgram");
	m_texture = CAssetMgr::GetInstance()->GetCubemapTexture("DefaultCubeMapTexture");
}

CCubeMap::~CCubeMap()
{}

void CCubeMap::RenderCubeMap(CCamera* _camera)
{
	glUseProgram(m_programID);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glDisable(GL_CULL_FACE);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
	glUniform1i(glGetUniformLocation(m_programID, "cubeSampler"), 0);

	glm::mat4 model = glm::scale(glm::mat4(), glm::vec3(1000.0f, 1000.0f, 1000.0f));
	glm::mat4 MVP = _camera->GetProj() * _camera->GetView() * model;
	glUniformMatrix4fv(glGetUniformLocation(m_programID, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));

	m_cubemapMesh->RenderMesh();
	
	glUseProgram(0);
	glDisable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}
