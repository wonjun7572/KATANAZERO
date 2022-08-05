#pragma once
#include "Obj.h"

class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Key_Input(void);
	void		Offset(void);
	void		Motion_Change(void);

	void		EnvCheck(void);

	void		Attacking(void);
	void		Rolling(void);
	void		WallJumping(void);

	void		Reset(void);

public:
	STATE		Get_CurState() { return m_eCurState; }
	STATE		Get_PreState() { return m_ePreState; }

	POINT		Get_Mousept() { return m_pt; }

	bool		Get_TurnBackTime() { return m_bTurnBackTime; }
	void		BackToPast();

	void		Set_Dead(bool _dead) { m_bDead = _dead; }
	void		Set_Frame(DWORD _frame) { g_dwTimer = _frame; }
	void		Set_LookDir(PLAYER_LOOKAT _lookat) { m_eLookDir = _lookat; }
	void		Set_EnvState(PLAYER_ENVIRONMENT _env) { m_eEevState = _env; }

	PLAYER_ENVIRONMENT Get_EnvState() { return m_eEevState; }
	void		Set_Render(int _pass) { m_iPass = _pass; }

	void		Set_ListClear()
	{
		m_tInfoList.clear();
		m_tFrameList.clear();
		m_ePreStateList.clear();
	}

	bool Get_Item() { return m_bItem; }
	void Set_Item(bool _item) { m_bItem = _item; }

	bool Get_Hide() { return m_bHide; }
	void Set_Hide(bool _hide) { m_bHide = _hide; }
	list<INFO>	Get_List() { return m_tInfoList; }
	bool	Get_KeyRPressing() { return m_bKeyRPressing; }

private:
	void GeneralRender(HDC hDC);
	void AlphaRender(HDC hDC);

protected:
	bool		m_bAttack = false;
	bool		m_bReset = false;

	float		 m_fFootY = 0.f;
	float		m_fPreFootY = 9999.f;

	// jump
	bool  m_bJump = false;
	float m_fMaxAbsJumpSpeed = 16.f;
	float m_fInitJumpSpeed = 15.f;
	float m_fCurJumpSpeed = 0.f;
	float m_fWallSpeed = 2.f;
	int	  m_iJumpCount = 0;
	// ~jump

	// wall
	int  m_iWallJumpCnt = 0;
	int  m_iWallJumpMaxCnt = 20;
	int  m_iWallJumpTickSpeed = 15;
	bool m_bWallJump = false;
	// ~wall

	// dash
	float m_fRollCoolTime = 0.3f;
	DWORD m_dwRollWaitTime;
	bool  m_bRoll = false;
	int   m_iRollCnt = 0;
	int   m_iRollMaxCnt = 15;
	float m_fRollSpeed = 15.f;
	// ~dash

	float		m_fHeight = 0.f;

	DWORD		m_dwTimer = 0;
	POINT		m_pt;
	STATE		m_ePreState;
	STATE		m_eCurState;
	PLAYER_ENVIRONMENT m_eEevState;

	// 되돌아가기
	list<INFO>  m_tInfoList;
	list<STATE> m_ePreStateList;
	list<FRAME> m_tFrameList;

	bool		m_bDeadState = false;
	bool		m_bTurnBackTime = false;

	bool		m_bItem = false;
	bool		m_bHide = false;

	int			m_iShakeCamera = 20;

	int			m_iCount = 0;

	bool		m_bSlowInSound  = false;
	bool		m_bSlowOutSound = false;
	bool		m_bDeadSound	= false;
	bool		m_bPast			= false;
	bool		m_bSwordMove	= false;
	bool		m_bKeyRPressing = false;

	int m_iPass = 1; // 기본 제네럴값

	Gdiplus::Bitmap* m_pTexture[11];
	
	Gdiplus::Bitmap* m_pTexture_BossDead[2];

	Gdiplus::Graphics* m_pGraphics = nullptr;
};

