// This Inlcude 
#include "Component.h"

CComponent::CComponent() {}

CComponent::~CComponent() {}

void CComponent::SetGameObject(CGameObject* _gameObject)
{
	this->m_gameObject = _gameObject;
}

CGameObject* CComponent::GetGameObject() const
{
	return m_gameObject;
}

void CComponent::SetActive(bool _b)
{
	m_isActive = _b;
}

bool CComponent::IsActive() const
{
	return m_isActive;
}
