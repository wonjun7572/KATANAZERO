#include "stdafx.h"
#include "BossHead.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CBossHead::CBossHead()
{
}

CBossHead::~CBossHead()
{
}

void CBossHead::Initialize(void)
{
	m_tInfo = { 0.f, 0.f, 90.f, 28.f };
	m_eRenderGroup = EFFECT;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.dwFrameSpeed = 500;
	m_tFrame.dwFrameTime = GetTickCount();

	m_pTexture = Gdiplus::Bitmap::FromFile(L"../image/boss/boss_headground_8x2.bmp");

	Gdiplus::Color Alpha(0, 0, 0, 0);

	for (UINT i = 0; i < m_pTexture->GetHeight(); ++i)
	{
		for (UINT j = 0; j < m_pTexture->GetWidth(); ++j)
		{
			Gdiplus::Color color;
			m_pTexture->GetPixel(j, i, &color);

			if (color.GetR() == 255 && color.GetG() == 0 && color.GetB() == 255)
				m_pTexture->SetPixel(j, i, Alpha);
			else
				m_pTexture->SetPixel(j, i, Gdiplus::Color::Black);
		}
	}
}

int CBossHead::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_tFrame.iFrameStart != m_tFrame.iFrameEnd)
	{
		Move_Frame();
	}
	Update_Rect();
	return OBJ_NOEVENT;
}

void CBossHead::Late_Update(void)
{
}

void CBossHead::Render(HDC hDC)
{

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_pGraphics == nullptr)
		m_pGraphics = Gdiplus::Graphics::FromHDC(hDC);

	if (m_eDir == DIR_RIGHT)
	{
		m_pGraphics->DrawImage(m_pTexture,
			m_tRect.left + iScrollX, m_tRect.top + iScrollY,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * m_tFrame.iMotion,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			UnitPixel);
	}
	else if (m_eDir == DIR_LEFT)
	{
		m_pGraphics->DrawImage(m_pTexture,
			m_tRect.left + iScrollX, m_tRect.top + iScrollY,
			630 - (int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * m_tFrame.iMotion,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			UnitPixel);
	}
}

void CBossHead::Release(void)
{
}
