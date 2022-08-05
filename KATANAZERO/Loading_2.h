#pragma once
#include "Scene.h"
class CLoading_2 :
	public CScene
{
public:
	CLoading_2();
	virtual ~CLoading_2();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

