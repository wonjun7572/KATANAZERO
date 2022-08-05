#pragma once
#include "Scene.h"
class CLoading_3 :
	public CScene
{
public:
	CLoading_3();
	virtual ~CLoading_3();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

