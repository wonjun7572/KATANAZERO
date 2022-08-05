#pragma once
#include "Obj.h"
class CLazerLong :
	public CObj
{
public:
	CLazerLong();
	virtual ~CLazerLong();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	CObj* m_pPlayer = nullptr;
};

