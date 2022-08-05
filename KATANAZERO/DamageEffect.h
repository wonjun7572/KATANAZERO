#pragma once
#include "Obj.h"
class CDamageEffect :
	public CObj
{
public:
	CDamageEffect();
	virtual ~CDamageEffect();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	POINT		m_tPoint[3];
	DWORD		m_dwOldTime;
	CObj*		m_pPlayer;

	bool		m_bGetAngle = false;
};

