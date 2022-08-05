#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	// �������� �ٷ� �������ִ� �Լ�
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}

	// X�� �� ��ŭ ���ϰų� ���ų�
	void		Set_PosX(float _fX) { m_tInfo.fX += _fX; }

	// Y�� �� ��ŭ ���ϰų� ���ų�
	void		Set_PosY(float _fY) { m_tInfo.fY += _fY; }

	// �𷺼� ����
	void		Set_Dir(DIR eDir) { m_eDir = eDir; }

	// ���� ����
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }

	// Ÿ�� ����
	void		Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }

	// �ִϸ��̼��� ���� ������Ű ����
	void		Set_FrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }

	void		Set_Size(float _fCX, float _fCY)
	{
		m_tInfo.fCX = _fCX;
		m_tInfo.fCY = _fCY;
	}

	void		Set_Alpha(int _alpha) { m_iAlpha = _alpha; }
	
	const RECT&		Get_Rect(void) const { return m_tRect; }
	const INFO&		Get_Info(void) const { return m_tInfo; }
	void			Kill_Obj(void) { m_bDead = true; }
	bool			Get_Dead(void) { return m_bDead; }

	const DIR&		Get_Dir(void) const { return m_eDir; }

	const RENDERID	Get_RenderID(void) const { return m_eRenderGroup; }
	const PLAYER_LOOKAT Get_playerLook() { return m_eLookDir; }

public:
	virtual void	Initialize(void)	PURE;
	virtual int		Update(void)		PURE;
	virtual void	Late_Update(void)	PURE;
	virtual void	Render(HDC hDC)		PURE;
	virtual void	Release(void)		PURE;
	int			Get_ID() { return m_iID; }

protected:
	void			Update_Rect(void);
	void			Move_Frame(void);

protected:
	int			m_iID = 0;
	INFO			m_tInfo;
	RECT		m_tRect;
	FRAME		m_tFrame;

	float		m_fSpeed		= 0.f;
	float		m_fAngle		= 0.f;
	float		m_fDiagonal		= 0.f;

	int			m_iAniCount		= 0;
	int			m_iAlpha		= 0;

	bool		m_bDead;

	CObj*		m_pTarget;
	TCHAR*		m_pFrameKey;

	DIR				m_eDir;
	PLAYER_LOOKAT   m_eLookDir;
	RENDERID		m_eRenderGroup;
};