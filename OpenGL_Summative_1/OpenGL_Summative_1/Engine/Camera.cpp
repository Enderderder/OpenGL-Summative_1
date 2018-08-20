
// This Include
#include "Camera.h"

// Engine Include
#include "Input.h"

static CInput* p_Input = CInput::GetInstance();

CCamera::CCamera() :
	m_CameraFacing(glm::vec3(0.0f, 0.0f, -1.0f)),
	m_CameraNormal(glm::vec3(0.0f, 1.0f, 0.0f)),
	m_bPerspective(true),
	m_fov(45.0f),
	m_nearPlane(0.1f),
	m_farPlane(1000.0f),
	m_bIsControlling(false)
{}

CCamera::~CCamera()
{}

void CCamera::InitializeObject()
{
	CalcViewMatrix();
	SetProjectionMatrix();
}

void CCamera::Update()
{
	if (m_bIsControlling)
	{
		glm::vec3 resultVec;

		if (p_Input->g_cKeyState[(unsigned char)'w'] == INPUT_HOLD || 
			p_Input->g_cKeyState[(unsigned char)'w'] == INPUT_FIRST_PRESS)
		{
			resultVec.z -= 0.2f;
		}
		if ((p_Input->g_cKeyState[(unsigned char)'s'] == INPUT_HOLD || 
			p_Input->g_cKeyState[(unsigned char)'s'] == INPUT_FIRST_PRESS))
		{
			resultVec.z += 0.2f;
		}
		if ((p_Input->g_cKeyState[(unsigned char)'a'] == INPUT_HOLD ||
			p_Input->g_cKeyState[(unsigned char)'a'] == INPUT_FIRST_PRESS))
		{
			resultVec.x -= 0.2f;
		}
		if ((p_Input->g_cKeyState[(unsigned char)'d'] == INPUT_HOLD || 
			p_Input->g_cKeyState[(unsigned char)'d'] == INPUT_FIRST_PRESS))
		{
			resultVec.x += 0.2f;
		}
		if ((p_Input->g_cKeyState[(unsigned char)'r'] == INPUT_HOLD ||
			p_Input->g_cKeyState[(unsigned char)'r'] == INPUT_FIRST_PRESS))
		{
			resultVec.y += 0.2f;
		}
		if ((p_Input->g_cKeyState[(unsigned char)'f'] == INPUT_HOLD ||
			p_Input->g_cKeyState[(unsigned char)'f'] == INPUT_FIRST_PRESS))
		{
			resultVec.y -= 0.2f;
		}

		if (resultVec != glm::vec3())
		{
			// Add the speed force to the direction
			this->m_transform.position += resultVec;

			//this->m_velocity = glm::normalize(resultVec) * m_movementSpd;
		}
	}




	CalcViewMatrix();
	SetProjectionMatrix();
}

glm::mat4 CCamera::GetView() const
{
	return(m_ViewMatrix);
}

void CCamera::CalcViewMatrix()
{
	m_ViewMatrix = glm::lookAt(
		this->m_transform.position,
		this->m_transform.position + m_CameraFacing,
		m_CameraNormal);
}

glm::mat4 CCamera::GetProj() const
{
	return m_ProjectionMatrix;
}

void CCamera::SetProjectionMatrix()
{
	if (m_bPerspective)
	{
		m_ProjectionMatrix = glm::perspective(m_fov,
			(float)util::SCR_WIDTH / (float)util::SCR_HEIGHT, m_nearPlane, m_farPlane);
	} 
	else
	{
		m_ProjectionMatrix = glm::ortho((float)-(util::SCR_WIDTH / 2), (float)(util::SCR_WIDTH / 2),
			(float)-(util::SCR_HEIGHT / 2), (float)(util::SCR_HEIGHT / 2), m_nearPlane, m_farPlane);
	}
}

glm::vec3 CCamera::GetCameraFacing() const
{
	return(m_CameraFacing);
}
void CCamera::SetCameraFacing(glm::vec3 _Facing)
{
	m_CameraFacing = _Facing;

	CalcViewMatrix();
	SetProjectionMatrix();
}

glm::vec3 CCamera::GetCameraNormal() const
{
	return(m_CameraNormal);
}
void CCamera::SetCameraNormal(glm::vec3 _Normal)
{
	m_CameraNormal = _Normal;

	CalcViewMatrix();
	SetProjectionMatrix();
}