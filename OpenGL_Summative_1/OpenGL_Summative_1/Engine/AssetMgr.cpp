
// This Include
#include "AssetMgr.h"

// Engine Include
#include "ShaderLoader.h"
#include "Sprite.h"
#include "CubeMesh.h"
#include "CubemapMesh.h"
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
	CreateProgram("UnlitProgram", "Engine/Shaders/Unlit.vs", "Engine/Shaders/Unlit.fs");
	CreateProgram("BlinnPhongProgram", "Engine/Shaders/BlinnPhong.vs", "Engine/Shaders/BlinnPhong.fs");
	CreateProgram("CubemapProgram", "Engine/Shaders/CubeMap.vs", "Engine/Shaders/CubeMap.fs");

	/** Initialize Meshes */
	CreateMesh("DefaultCubeMesh", new CCubeMesh());
	CreateMesh("DefaultCubemapMesh", new CCubemapMesh());

	/** Initialize Textures */
	CreateTexture("Box", "Resources/Textures/Box.png");
	CreateTexture("Block", "Resources/Sprites/Block.png");

	/** Initialize Sprites */
	CreateSprite("Block", "Resources/Sprites/Block.png");

	/** initialize Cubemaps */
	std::vector<std::string> GameCubeMapPaths = {
		"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"back.jpg",
		"front.jpg"
	};
	CreateCubemapTexture("DefaultCubeMapTexture", GameCubeMapPaths);
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

GLuint CAssetMgr::GetTexture(std::string _name) const
{
	for (auto iter = m_textureMap.begin(); iter != m_textureMap.end(); ++iter)
	{
		if (iter->first == _name)
		{
			return iter->second;
		}
	}

	CDebug::Log("Unable to grab texture from name.");
	return NULL;
}

GLuint CAssetMgr::GetCubemapTexture(std::string _name) const
{
	for (auto iter = m_cubemapTextureMap.begin(); iter != m_cubemapTextureMap.end(); ++iter)
	{
		if (iter->first == _name)
		{
			return iter->second;
		}
	}

	CDebug::Log("Unable to grab cubemap texture from name.");
	return NULL;
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

void CAssetMgr::CreateTexture(std::string _name, const char* _pathName)
{
	/** Bind the texture */
	
	GLuint texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height;
	std::cout << "Loading Texture: " << _pathName << "\n";

	unsigned char* image = SOIL_load_image(
		_pathName,				// File path / Name
		&width,				// Output for the image width
		&height,			// Output for the image height
		0,					// Output for number of channels
		SOIL_LOAD_RGBA);	// Load RGB values only

	glTexImage2D(
		GL_TEXTURE_2D,		// Type of texture
		0,					// Mipmap level, 0 for base
		GL_RGBA,			// Number of color components in texture
		width,				// Width of the texture
		height,				// Height of the texture
		0,					// This value must be 0
		GL_RGBA,			// Format for the pixel data
		GL_UNSIGNED_BYTE,	// Data type for the pixel data
		image);				// Pointer to image data in memory

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	/************************************************************************/

	/** Load into the map */
	m_textureMap.insert(std::pair<std::string, GLuint>(_name, texture));
}

void CAssetMgr::CreateCubemapTexture(std::string _name, std::vector<std::string> _textureNames)
{
	GLuint texture;

	// Bind each image into the cube map
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	int width, height;
	unsigned char* image;
	for (GLuint i = 0; i < 6; ++i)
	{
		std::string fullPathName = "Resources/Textures/CubeMap/";
		fullPathName.append(_textureNames[i]);

		image = SOIL_load_image(fullPathName.c_str(),
			&width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
			width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	}

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	// Free memory and unbind the texture type
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	/************************************************************************/

	/** Load into the map */
	m_cubemapTextureMap.insert(std::pair<std::string, GLuint>(_name, texture));

}
