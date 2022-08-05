#pragma once
#include "Obj.h"
class CJumpDustEffect :
	public CObj
{
public:
	CJumpDustEffect();
	virtual ~CJumpDustEffect();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

