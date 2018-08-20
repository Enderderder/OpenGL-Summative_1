
// This Include
#include "AssetMgr.h"

// Engine Include
#include "ShaderLoader.h"
#include "Sprite.h"
#include "CubeMesh.h"
#include "Debug.h"

#pragma region Singleton

// Static Variable
CAssetMgr* CAssetMgr::s_pAssetMgr = nullptr;

CAssetMgr* CAssetMgr::GetInstance()
{
	if (s_pAssetMgr == nullptr)
	{
		s_pAssetMgr = new CAssetMgr();
	}

	return s_pAssetMgr;
}

void CAssetMgr::DestroyInstance()
{
	delete s_pAssetMgr;
	s_pAssetMgr = nullptr;
}

CAssetMgr::CAssetMgr() {}
CAssetMgr::~CAssetMgr() {}

#pragma endregion Singleton

void CAssetMgr::InitializeAssets()
{
	/** Initialize Programs */
	CreateProgram("DefaultSpriteProgram", "Engine/Shaders/Sprite.vs", "Engine/Shaders/Sprite.fs");
	CreateProgram("UnlitProgram", "Engine/Shaders/Unlit.vs", "Engine/Shaders/Unlit.vs");

	/** Initialize Meshes */
	CreateMesh("DefaultCubeMesh", new CCubeMesh());

	/** Initialize Sprites */
	CreateSprite("Block", "Resources/Sprites/Block.png");
}

CSprite* CAssetMgr::GetSprite(std::string _name) const
{
	for (auto iter = m_spriteMap.begin(); iter != m_spriteMap.end(); ++iter)
	{
		if (iter->first == _name)
		{
			return iter->second;
		}
	}

	CDebug::Log("Unable to grab sprite from name.");
	return nullptr;
}

GLuint CAssetMgr::GetProgramID(std::string _name) const
{
	for (auto iter = m_programMap.begin(); iter != m_programMap.end(); ++iter)
	{
		if (iter->first == _name)
		{
			return iter->second;
		}
	}

	CDebug::Log("Unable to grab program ID from name.");
	return NULL;
}

CMesh* CAssetMgr::GetMesh(std::string _name) const
{
	for (auto iter = m_meshMap.begin(); iter != m_meshMap.end(); ++iter)
	{
		if (iter->first == _name)
		{
			return iter->second;
		}
	}

	CDebug::Log("Unable to grab mesh from name.");
	return nullptr;
}

void CAssetMgr::CreateProgram(std::string _name, const char* _vertexPath, const char* _fragmentPath)
{
	GLuint newProgram = ShaderLoader::CreateProgram(_vertexPath, _fragmentPath);

	m_programMap.insert(std::pair<std::string, GLuint>(_name, newProgram));
}

void CAssetMgr::CreateSprite(std::string _name, const char* _pathName)
{
	CSprite* newSprite = new CSprite();
	newSprite->CreateSprite(_pathName);

	m_spriteMap.insert(std::pair<std::string, CSprite*>(_name, newSprite));
}

void CAssetMgr::CreateMesh(std::string _name, CMesh* _mesh)
{
	m_meshMap.insert(std::pair<std::string, CMesh*>(_name, _mesh));
}
