#include "stdafx.h"
#include "SwordEffect.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "DamageEffect.h"
#include "Player.h"

CSwordEffect::CSwordEffect()
{
}

CSwordEffect::~CSwordEffect()
{
	Release();
}

void CSwordEffect::Initialize(void)
{
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	m_tInfo = { 0 ,0, 210.f, 210.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/player/Player_Slash24.bmp", L"PLAYER_ATTACK_SLASH");
	m_eRenderGroup = EFFECT;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CSwordEffect::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CSwordEffect::Late_Update(void)
{
	if (!m_bGetAngle)
	{
		float fWeight = dynamic_cast<CPlayer*>(m_pPlayer)->Get_Mousept().x - m_tInfo.fX;
		float fHeight = dynamic_cast<CPlayer*>(m_pPlayer)->Get_Mousept().y - m_tInfo.fY;
		float fDiagonal = sqrtf(fWeight * fWeight + fHeight * fHeight);

		float fRadian = acosf(fWeight / fDiagonal);
		if (m_tInfo.fY < dynamic_cast<CPlayer*>(m_pPlayer)->Get_Mousept().y)
			fRadian *= -1.f;

		m_fAngle = fRadian / PI * 180;

		m_bGetAngle = true;
	}
}

void CSwordEffect::Render(HDC hDC)
{
	// AttackSlash
	HDC hSlashDC = CBmpMgr::Get_Instance()->Find_Img(L"PLAYER_ATTACK_SLASH");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (0 <= m_fAngle && m_fAngle <= 15)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,								
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,									
			(int)m_tInfo.fCY,
			hSlashDC,											
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,			
			0,
			(int)m_tInfo.fCX,										
			(int)m_tInfo.fCY,
			RGB(0, 0, 0));
	}
	else if (15 < m_fAngle && m_fAngle <= 30)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hSlashDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(0, 0, 0));
	}
	else if (30 < m_fAngle && m_fAngle <= 45)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hSlashDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * 2,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(0, 0, 0));
	}
	else if (45 < m_fAngle && m_fAngle <= 60)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hSlashDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * 3,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(0, 0, 0));
	}
	else if (60 < m_fAngle && m_fAngle <= 75)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hSlashDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * 4,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(0, 0, 0));
	}
	else if (75 < m_fAngle && m_fAngle <= 90)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hSlashDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * 5,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(0, 0, 0));
	}
	else if (90 < m_fAngle && m_fAngle <= 105)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hSlashDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * 6,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(0, 0, 0));
	}
	else if (105 < m_fAngle && m_fAngle <= 120)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hSlashDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * 7,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(0, 0, 0));
	}
	else if (120 < m_fAngle && m_fAngle <= 135)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hSlashDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * 8,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(0, 0, 0));
	}
	else if (135 < m_fAngle && m_fAngle <= 150)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hSlashDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY *9,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(0, 0, 0));
	}
	else if (150 < m_fAngle && m_fAngle <= 165)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hSlashDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * 10,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(0, 0, 0));
	}
	else if (165 < m_fAngle && m_fAngle <= 180)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hSlashDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * 11,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(0, 0, 0));
	}
	else if (-180 <= m_fAngle && m_fAngle <= -165)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hSlashDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * 12,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(0, 0, 0));
	}
	else if (-165 < m_fAngle && m_fAngle <= -150)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hSlashDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * 13,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(0, 0, 0));
	}
	else if (-150 < m_fAngle && m_fAngle <= -135)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hSlashDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * 14,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(0, 0, 0));
	}
	else if (-135 < m_fAngle && m_fAngle <= -120)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hSlashDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * 15,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(0, 0, 0));
	}
	else if (-120 < m_fAngle && m_fAngle <= -105)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hSlashDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * 16,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(0, 0, 0));
	}
	else if (-105 < m_fAngle && m_fAngle <= -90)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hSlashDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * 17,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(0, 0, 0));
	}
	else if (-90 < m_fAngle && m_fAngle <= -75)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hSlashDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * 18,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(0, 0, 0));
	}
	else if (-75 < m_fAngle && m_fAngle <= -60)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hSlashDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * 19,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(0, 0, 0));
	}
	else if (-60 < m_fAngle && m_fAngle <= -45)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hSlashDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * 20,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(0, 0, 0));
	}
	else if (-45 < m_fAngle && m_fAngle <= -30)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hSlashDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * 21,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(0, 0, 0));
	}
	else if (-30 < m_fAngle && m_fAngle <= -15)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hSlashDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * 22,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(0, 0, 0));
	}
	else if (-15 < m_fAngle && m_fAngle <= 0)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hSlashDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * 23,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(0, 0, 0));
	}

	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		m_bDead = true;
}

void CSwordEffect::Release(void)
{
}
