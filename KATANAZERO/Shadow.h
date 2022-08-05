#pragma once
#include "Player.h"

class CBitMap;
class CShadow :
	public CPlayer
{
public:
	CShadow();
	virtual ~CShadow();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void SetTime(DWORD _plusTime) { m_PlusTime = _plusTime; }
	void SetAlpha(int _alpha) { m_iAlpha = _alpha; }
	void Motion_Change();

private:
	CObj*	 m_pPlayer;

	DWORD    m_OldTime;

	DWORD    m_PlusTime;

	bool	 m_bRender = false;

	BLENDFUNCTION m_BlendFunction;
	int			  m_iAlpha;

	HDC		m_AlphaDC;
};

