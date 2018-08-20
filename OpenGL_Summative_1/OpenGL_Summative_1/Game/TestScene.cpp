
// This Include
#include "TestScene.h"

// Inlcude the game classes
#include "Game/GameClasses.h"
#include "Engine/Camera.h"


void CTestScene::InitailizeScene()
{
	__super::InitailizeScene();

	/** Create Camera Object */

	this->m_MainCamera = new CCamera();
	
	/** Create game objects in the scenes */

	this->m_vGameObj.push_back(new CSpaceShip());

}