#pragma once
#include "Scene.h"
class CBossStage :
	public CScene
{
public:
	CBossStage();
	virtual ~CBossStage();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	bool m_bLoadLine = false;
	bool m_bEnding = false;
	bool m_bReleaseUI = false;
};

