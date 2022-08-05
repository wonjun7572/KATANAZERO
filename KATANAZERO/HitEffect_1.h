#pragma once
#include "Obj.h"
class CHitEffect_1 :
	public CObj
{
public:
	CHitEffect_1();
	virtual ~CHitEffect_1();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

