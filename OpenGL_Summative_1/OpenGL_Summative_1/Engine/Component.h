#pragma once

// Forward Declare
class CGameObject;


class CComponent
{
public:
	CComponent();
	~CComponent();

protected:

	CGameObject* m_gameObject;
	bool m_isActive;

// Membre Funciton
public:

	void SetGameObject(CGameObject* _gameObject);
	CGameObject* GetGameObject() const;

	virtual void Update() {}
	virtual void Initialize() {}
	virtual void OnDestroy() {}

	void SetActive(bool);
	bool IsActive() const;
};

