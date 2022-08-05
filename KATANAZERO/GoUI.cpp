#include "stdafx.h"
#include "GoUI.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CGoUI::CGoUI()
{
}

CGoUI::~CGoUI()
{
}

void CGoUI::Initialize(void)
{
	m_tInfo = { 0.f, 0.f, 78.f, 40.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/effect/hud_go.bmp", L"HUD_GO_UI");
	m_pFrameKey = L"HUD_GO_UI";
	m_eRenderGroup = UI;
	m_BlendFunction.BlendOp = AC_SRC_OVER;
	m_BlendFunction.BlendFlags = 0;
	m_BlendFunction.AlphaFormat = 0;
	m_iAlpha = 255;
}

int CGoUI::Update(void)
{
	if (m_iAlpha <= 0)
	{
		m_iAlpha = 255;
	}
	else
	{
		m_iAlpha -= 6;
	}
	Update_Rect();
	return 0;
}

void CGoUI::Late_Update(void)
{
}

void CGoUI::Render(HDC hDC)
{
		int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

		HDC AlphaDC = CreateCompatibleDC(hMemDC);
		HBITMAP TempDC = CreateCompatibleBitmap(hMemDC, WINCX, WINCY);
		HBITMAP	OldTempDC = (HBITMAP)SelectObject(AlphaDC, TempDC);
		m_BlendFunction.SourceConstantAlpha = m_iAlpha;

		GdiTransparentBlt(AlphaDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));

		GdiTransparentBlt(AlphaDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hMemDC,
			0,
			0,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));

		GdiAlphaBlend(hDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			AlphaDC,
			m_tRect.left + iScrollX,
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			m_BlendFunction);

		DeleteObject(SelectObject(AlphaDC, OldTempDC));
		DeleteDC(AlphaDC);
}

void CGoUI::Release(void)
{
}
