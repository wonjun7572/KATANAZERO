#pragma once
#include "Obj.h"
class CExplosion :
	public CObj
{
public:
	CExplosion();
	virtual ~CExplosion();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

