#pragma once
#include "Scene.h"
class CLoading_Boss :
	public CScene
{
public:
	CLoading_Boss();
	virtual ~CLoading_Boss();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

