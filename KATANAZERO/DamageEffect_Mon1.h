#pragma once
#include "Obj.h"
class CDamageEffect_Mon1 :
	public CObj
{
public:
	CDamageEffect_Mon1();
	virtual ~CDamageEffect_Mon1();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

