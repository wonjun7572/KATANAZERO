#pragma once
#include "Obj.h"
class CMonster_1 :
	public CObj
{
public:
	CMonster_1();
	virtual ~CMonster_1();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void		Graviting(void);
	void		Motion_Change(void);

	void		Attack(void);
	void		InfoToRect();
	bool		Check_Sphere(CObj* pDest, INFO* pSour);
	void		Walking(void);

private:
	void		Reset();
	void		Set_ListClear()
	{
		m_tInfoList.clear();
		m_tFrameList.clear();
		m_ePreStateList.clear();
	}
	void		BackToPast();

private:
	STATE		m_ePreState;
	STATE		m_eCurState;

	bool		m_bLineCol		= false;
	bool		m_bAniStop		= false;
	bool		m_bAttack		= false;
	
	bool		m_bWalk			= false;
	bool		m_bJump			= false;
	bool		m_bRealJump		= false;

	bool		m_bHitEffect	= false;
	bool		m_bHitEffect_1  = false;

	RECT		m_rtPlayerRectCheck;
	INFO		m_tPlayerCheck;

	CObj*		m_pPlayer;

	DWORD		m_dwOldTime;

	float		m_fWalkCount	= 0.f;
	float		m_fJumpPower	= 0.f;
	float		m_fJumpTime		= 0.f;

	bool		m_bFindPlayer	= false;

	DWORD		m_dwBackToTimer;

	// 되돌아가기
	list<INFO>  m_tInfoList;
	list<STATE> m_ePreStateList;
	list<FRAME> m_tFrameList;

	bool		m_bReset = false;
};

