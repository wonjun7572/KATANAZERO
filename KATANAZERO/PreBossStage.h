#pragma once
#include "Scene.h"
class CPreBossStage :
	public CScene
{
public:
	CPreBossStage();
	virtual ~CPreBossStage();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	DWORD m_dwTimer;

	DWORD m_dwT[2];

	bool		m_bDown = false;
	bool		m_bExplosion = false;

	int			m_iNum = 0;
};

