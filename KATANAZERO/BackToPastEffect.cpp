#include "stdafx.h"
#include "BackToPastEffect.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
CBackToPastEffect::CBackToPastEffect()
{
}

CBackToPastEffect::~CBackToPastEffect()
{
}

void CBackToPastEffect::Initialize(void)
{
	m_tInfo = { 0.f, 0.f, 1280.f, 720.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/BackToPast.bmp", L"BACK_TO_PAST");
	m_pFrameKey = L"BACK_TO_PAST";
	m_eRenderGroup = UI;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
	m_BlendFunction.BlendOp = AC_SRC_OVER;
	m_BlendFunction.BlendFlags = 0;
	m_BlendFunction.AlphaFormat = 0;
	m_iAlpha = 255;
}

int CBackToPastEffect::Update(void)
{
	if (m_iAlpha <= 0)
	{
		m_iAlpha = 255;
	}
	else
	{
		m_iAlpha -= 10;
	}

	Move_Frame();
	Update_Rect();
	return 0;
}

void CBackToPastEffect::Late_Update(void)
{

}

void CBackToPastEffect::Render(HDC hDC)
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
		0,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));

	GdiAlphaBlend(hDC,
		0,
	    0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		AlphaDC,
		0,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		m_BlendFunction);

	DeleteObject(SelectObject(AlphaDC, OldTempDC));
	DeleteDC(AlphaDC);
}

void CBackToPastEffect::Release(void)
{
}
