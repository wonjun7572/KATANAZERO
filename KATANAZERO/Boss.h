#pragma once
#include "Obj.h"
class CBoss :
	public CObj
{
	enum STATE_BOSS
	{
		IDLE,
		GROUND_ANI,
		TELEPORT_ANI,
		WALL_ANI,
		WALL_GRAB,
		BOSS_DEAD,
		BOSS_DEAD_AFTER,
		HURT_RECOVER,
		BOSS_PATTERN_IN,
		BOSS_NO_HEAD,
		MOTION_END
	};

public:
	CBoss();
	virtual ~CBoss();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void Late_Update(void)override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	void	Motion_Change();
	void EnvCheck();
	void		Set_EnvState(PLAYER_ENVIRONMENT _env) { m_eEevState = _env; }

	bool		Check_Sphere(CObj* pDest, INFO* pSour);
	int		Get_HP() { return m_iHp; }

	void		GroundAttack(int _dir);
	void		AirAttack();
	void		WallAttack();

	bool		Get_RealDead() { return m_bRealDead; }

	void		Set_ListClear()
	{
		m_tInfoList.clear();
		m_tFrameList.clear();
		m_ePreStateList.clear();
	}
	void		Set_Frame(DWORD _frame) { g_dwTimer = _frame; }
	void		Reset();
private:
	STATE_BOSS		m_ePreState;
	STATE_BOSS		m_eCurState;

	DWORD		m_dwAttackTimer[20];

	DWORD		m_dwHitTimer;

	DWORD		m_dwTimer;

	DWORD		m_dwResetTimer;

	bool		m_bGroundAttack = false;
	bool		m_bTeleportAttack = false;
	bool		m_bWallAttack = false;
	bool		m_bAttack = false;

	bool		m_bDown = false;

	float		m_fJumpPower = 0.f;
	float		m_fJumpTime = 0.f;

	CObj*		m_pPlayer = nullptr;

	bool		m_bStart = false;

	bool		m_bPatternFinish = false;

	int			m_iHp = 10;

	float		m_fFootY = 0.f;
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

	PLAYER_ENVIRONMENT m_eEevState;

	bool	m_bRealDead = false;
	bool	m_bFinished = false;

	bool	m_bBossHead = false;

	// 되돌아가기
	list<INFO>			m_tInfoList;
	list<STATE_BOSS>	m_ePreStateList;
	list<FRAME>			m_tFrameList;
	bool				m_bReset = false;
private:
	Gdiplus::Bitmap* m_pTexture;
	Gdiplus::Graphics* m_pGraphics = nullptr;
};

