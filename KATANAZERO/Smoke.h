#pragma once
#include "Obj.h"
class CSmoke :
	public CObj
{
public:
	CSmoke();
	virtual ~CSmoke();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	bool		Get_Damage() { return m_bDamaged; }

	void		InfoToRect();
	bool		Check_Sphere(CObj* pDest, INFO* pSour);
	POINT		m_tPoint[3];
	float		m_fRotAngle = 0.f;
	CObj*		m_pPlayer = nullptr;
	RECT		m_rtPlayerRectCheck;
	INFO		m_tPlayerCheck;

private:
	bool		m_bGas = false;
	bool		m_bRealDead = false;
	bool		m_bDamaged = true;
	DWORD		m_dwTimer;
};



