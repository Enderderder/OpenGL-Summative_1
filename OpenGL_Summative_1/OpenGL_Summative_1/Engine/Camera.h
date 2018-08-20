#ifndef CAMERA_H
#define CAMERA_H

// Inherited Include
#include "GameObject.h"

class CCamera : public CGameObject
{
public:
	CCamera();
	~CCamera();

	virtual void InitializeObject() override;
	virtual void Update() override;

	glm::mat4 GetView() const;
	void CalcViewMatrix();

	glm::mat4 GetProj() const;
	void SetProjectionMatrix();

	glm::vec3 GetCameraFacing() const;
	void SetCameraFacing(glm::vec3 _Facing);

	glm::vec3 GetCameraNormal() const;
	void SetCameraNormal(glm::vec3 _Normal);


public: /** Configuration for the camera */

	bool m_bPerspective;
	float m_fov;
	float m_nearPlane;
	float m_farPlane;

	bool m_bIsControlling;


private: /** Member variables */

	glm::vec3 m_CameraFacing;
	glm::vec3 m_CameraNormal;

	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;
};

#endif // !CAMERA_H