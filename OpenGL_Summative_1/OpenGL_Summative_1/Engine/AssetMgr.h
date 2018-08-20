#pragma once

// Global Include
#include "Utility.h"

// Forward Declare
class CSprite;
class CMesh;


class CAssetMgr
{

#pragma region Singleton
public:

	static CAssetMgr* GetInstance();
	static void DestroyInstance();

private:
	CAssetMgr();
	~CAssetMgr();

	CAssetMgr(const CAssetMgr& _kr) = delete;
	CAssetMgr& operator= (const CAssetMgr& _kr) = delete;

protected:
	static CAssetMgr* s_pAssetMgr;

#pragma endregion

public:

	void InitializeAssets();

	CSprite* GetSprite(std::string _name) const;
	GLuint GetProgramID(std::string _name) const;
	CMesh* GetMesh(std::string _name) const;


private:

	void CreateProgram(std::string _name, const char* _vertexPath, const char* _fragmentPath);

	void CreateSprite(std::string _name, const char* _pathName);

	void CreateMesh(std::string _name, CMesh* _mesh);


private:
	/** Map collection of sprites with a string name */
	std::map<std::string, CSprite*> m_spriteMap;

	/** Map collection of meshes */
	std::map<std::string, CMesh*> m_meshMap;

	/** Map collection of programs with a string name */
	std::map<std::string, GLuint> m_programMap;



};

