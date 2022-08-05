#pragma once
#include "Obj.h"
class CBottleWreck :
	public CObj
{
public:
	CBottleWreck();
	virtual ~CBottleWreck();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void Graviting(void);
private:
	float		m_fJumpPower = 0.f;
	float		m_fJumpTime = 0.f;
	bool		m_bJump = true;
	bool		m_bLineCol = false;

	float		m_fPlusX = 0.f;
};

