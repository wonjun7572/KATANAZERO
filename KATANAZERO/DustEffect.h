#pragma once
#include "Obj.h"
class CDustEffect :
	public CObj
{
public:
	CDustEffect();
	virtual ~CDustEffect();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

