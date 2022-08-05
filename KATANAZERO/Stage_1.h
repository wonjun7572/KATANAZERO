#pragma once
#include "Scene.h"
class CStage_1 :
	public CScene
{
public:
	CStage_1();
	virtual ~CStage_1();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	bool m_bMonClear = false;
	bool m_bGoUI = false;
	int m_iMonCount = 0;
	bool m_iMonCheck = false;

	bool m_bCurtain = false;
};

