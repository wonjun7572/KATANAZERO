#pragma once
#include "Obj.h"
class CSwordEffect :
	public CObj
{
public:
	CSwordEffect();
	virtual ~CSwordEffect();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	CObj*		m_pPlayer;
	bool		m_bGetAngle = false;
};

