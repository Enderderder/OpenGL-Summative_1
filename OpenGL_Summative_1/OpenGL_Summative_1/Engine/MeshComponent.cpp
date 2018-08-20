
// This Include 
#include "MeshComponent.h"

// Engine Include


CMeshComponent::CMeshComponent() {}

CMeshComponent::~CMeshComponent() {}

void CMeshComponent::SetMesh(CMesh* _mesh)
{
	m_mesh = _mesh;
}

void CMeshComponent::SetTexture(GLuint _texture)
{
	m_texture = _texture;
}

void CMeshComponent::RenderMesh(CCamera* _camera)
{

}
