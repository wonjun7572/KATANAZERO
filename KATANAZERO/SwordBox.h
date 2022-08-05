#pragma once
#include "Obj.h"
class CSwordBox :
	public CObj
{
public:
	CSwordBox();
	virtual ~CSwordBox();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void RotationCheck();

private:
	CObj*		m_pPlayer;
	bool		m_bGetAngle = false;
	bool		m_bChangePos = false;

	bool		m_bSwordEffect = false;
};

