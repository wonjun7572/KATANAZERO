#pragma once
#include "Scene.h"
class CStage_2 :
	public CScene
{
public:
	CStage_2();
	virtual ~CStage_2();

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
};

