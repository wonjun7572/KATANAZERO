#pragma once
#include "Obj.h"
class CBBatteryGageUI :
	public CObj
{
public:
	CBBatteryGageUI();
	virtual ~CBBatteryGageUI();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void	SetWeight(int _iWeight) { m_iWeight = _iWeight; }

private:
	int m_iWeight = 0;
	DWORD m_dwTimer;
};

