#pragma once
#include "Obj.h"
class CGroundLazer :
	public CObj
{
public:
	CGroundLazer();
	virtual ~CGroundLazer();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

