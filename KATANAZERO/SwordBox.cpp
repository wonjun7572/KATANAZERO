#include "stdafx.h"
#include "SwordBox.h"
#include "ObjMgr.h"
#include "Player.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "SwordEffect.h"
CSwordBox::CSwordBox()
{
}


CSwordBox::~CSwordBox()
{
}

void CSwordBox::Initialize(void)
{
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	m_tInfo = { 0 ,0, 120.f, 120.f };
	m_eRenderGroup = EFFECT;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CSwordBox::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!m_bGetAngle)
	{
		float fWeight = dynamic_cast<CPlayer*>(m_pPlayer)->Get_Mousept().x - m_tInfo.fX;
		float fHeight = dynamic_cast<CPlayer*>(m_pPlayer)->Get_Mousept().y - m_tInfo.fY;
		 m_fDiagonal = sqrtf(fWeight * fWeight + fHeight * fHeight);

		float fRadian = acosf(fWeight / m_fDiagonal);
		if (m_tInfo.fY < dynamic_cast<CPlayer*>(m_pPlayer)->Get_Mousept().y)
			fRadian *= -1.f;

		m_fAngle = fRadian / PI * 180;

		m_bGetAngle = true;
	}
	RotationCheck();
	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CSwordBox::Late_Update(void)
{
	
}

void CSwordBox::Render(HDC hDC)
{
	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		m_bDead = true;
}

void CSwordBox::Release(void)
{
}

void CSwordBox::RotationCheck()
{
	if (0 <= m_fAngle && m_fAngle <= 15)
	{
		if (!m_bChangePos)
		{
			m_tInfo.fX += 70.f;
			m_bChangePos = true;
		}
	}
	else if (15 < m_fAngle && m_fAngle <= 30)
	{
		if (!m_bChangePos)
		{
			m_tInfo.fX += 60.f;
			m_tInfo.fY -= 10.f;
			m_bChangePos = true;
		}
	}
	else if (30 < m_fAngle && m_fAngle <= 45)
	{
		if (!m_bChangePos)
		{
			m_tInfo.fX += 50.f;
			m_tInfo.fY -= 20.f;
			m_bChangePos = true;
		}
	}
	else if (45 < m_fAngle && m_fAngle <= 60)
	{
		if (!m_bChangePos)
		{
			m_tInfo.fX += 40.f;
			m_tInfo.fY -= 30.f;
			m_bChangePos = true;
		}
	}
	else if (60 < m_fAngle && m_fAngle <= 75)
	{
		if (!m_bChangePos)
		{
			m_tInfo.fX += 30.f;
			m_tInfo.fY -= 40.f;
			m_bChangePos = true;
		}
	}
	else if (75 < m_fAngle && m_fAngle <= 90)
	{
		if (!m_bChangePos)
		{
			m_tInfo.fX += 20.f;
			m_tInfo.fY -= 50.f;
			m_bChangePos = true;
		}
	}
	else if (90 < m_fAngle && m_fAngle <= 105)
	{
		if (!m_bChangePos)
		{
			m_tInfo.fY -= 70.f;
			m_bChangePos = true;
		}
	}
	else if (105 < m_fAngle && m_fAngle <= 120)
	{
		if (!m_bChangePos)
		{
			m_tInfo.fY -= 70.f;
			m_bChangePos = true;
		}
	}
	else if (120 < m_fAngle && m_fAngle <= 135)
	{
		if (!m_bChangePos)
		{
			m_tInfo.fX -= 10.f;
			m_tInfo.fY -= 50.f;
			m_bChangePos = true;
		}
	}
	else if (135 < m_fAngle && m_fAngle <= 150)
	{
		if (!m_bChangePos)
		{
			m_tInfo.fX -= 30.f;
			m_tInfo.fY -= 50.f;
			m_bChangePos = true;
		}
	}
	else if (150 < m_fAngle && m_fAngle <= 165)
	{
		if (!m_bChangePos)
		{
			m_tInfo.fX -= 50.f;
			m_tInfo.fY -= 50.f;
			m_bChangePos = true;
		}
	}
	else if (165 < m_fAngle && m_fAngle <= 180)
	{
		if (!m_bChangePos)
		{
			m_tInfo.fX -= 70.f;
			m_bChangePos = true;
		}
	}
	else if (-180 <= m_fAngle && m_fAngle <= -165)
	{
		if (!m_bChangePos)
		{
			m_tInfo.fX -= 70.f;
			m_bChangePos = true;
		}
	}
	else if (-165 < m_fAngle && m_fAngle <= -150)
	{
		if (!m_bChangePos)
		{
			m_tInfo.fX -= 60.f;
			m_tInfo.fY += 10.f;
			m_bChangePos = true;
		}
	}
	else if (-150 < m_fAngle && m_fAngle <= -135)
	{
		if (!m_bChangePos)
		{
			m_tInfo.fX -= 50.f;
			m_tInfo.fY += 25.f;
			m_bChangePos = true;
		}
	}
	else if (-135 < m_fAngle && m_fAngle <= -120)
	{
		if (!m_bChangePos)
		{
			m_tInfo.fX -= 40.f;
			m_tInfo.fY += 40.f;
			m_bChangePos = true;
		}
	}
	else if (-120 < m_fAngle && m_fAngle <= -105)
	{
		if (!m_bChangePos)
		{
			m_tInfo.fX -= 40.f;
			m_tInfo.fY += 55.f;
			m_bChangePos = true;
		}
	}
	else if (-105 < m_fAngle && m_fAngle <= -90)
	{
		if (!m_bChangePos)
		{
			m_tInfo.fY += 70.f;
			m_bChangePos = true;
		}
	}
	else if (-90 < m_fAngle && m_fAngle <= -75)
	{
		if (!m_bChangePos)
		{
			m_tInfo.fY += 70.f;
			m_bChangePos = true;
		}
	}
	else if (-75 < m_fAngle && m_fAngle <= -60)
	{
		if (!m_bChangePos)
		{
			m_tInfo.fX += 10.f;
			m_tInfo.fY += 70.f;
			m_bChangePos = true;
		}
	}
	else if (-60 < m_fAngle && m_fAngle <= -45)
	{
		if (!m_bChangePos)
		{
			m_tInfo.fX += 20.f;
			m_tInfo.fY += 52.5f;
			m_bChangePos = true;
		}
	}
	else if (-45 < m_fAngle && m_fAngle <= -30)
	{
		if (!m_bChangePos)
		{
			m_tInfo.fX += 30.f;
			m_tInfo.fY += 35;
			m_bChangePos = true;
		}
	}
	else if (-30 < m_fAngle && m_fAngle <= -15)
	{
		if (!m_bChangePos)
		{
			m_tInfo.fX += 40.f;
			m_tInfo.fY += 17.5;
			m_bChangePos = true;
		}
	}
	else if (-15 < m_fAngle && m_fAngle <= 0)
	{
		if (!m_bChangePos)
		{
			m_tInfo.fX += 50.f;
			m_bChangePos = true;
		}
	}
	if (!m_bSwordEffect)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CSwordEffect>::Create(m_pPlayer->Get_Info().fX, m_pPlayer->Get_Info().fY));
		m_bSwordEffect = true;
	}
}
