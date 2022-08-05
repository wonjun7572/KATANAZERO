#include "stdafx.h"
#include "Curtain.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
CCurtain::CCurtain()
{
}

CCurtain::~CCurtain()
{
}

void CCurtain::Initialize(void)
{
	m_tInfo = { 0.f,0.f,1280.f,720.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/Test.bmp", L"RESET");
	m_pFrameKey = L"RESET";
	m_eRenderGroup = UI;
	m_BlendFunction.BlendOp = AC_SRC_OVER;
	m_BlendFunction.BlendFlags = 0;
	m_BlendFunction.AlphaFormat = 0;
	m_iAlpha = 255;
}

int CCurtain::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	return 0;
}

void CCurtain::Late_Update(void)
{
}

void CCurtain::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	HDC AlphaDC = CreateCompatibleDC(hMemDC);
	HBITMAP TempDC = CreateCompatibleBitmap(hMemDC, WINCX, WINCY);
	HBITMAP	OldTempDC = (HBITMAP)SelectObject(AlphaDC, TempDC);
	m_BlendFunction.SourceConstantAlpha = m_iAlpha;

	GdiTransparentBlt(AlphaDC,
		m_tRect.left + iScrollX + 400.f,
		m_tRect.top + iScrollY - 200.f,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hDC,
		m_tRect.left + iScrollX + 400.f,
		m_tRect.top + iScrollY - 200.f,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));

	GdiTransparentBlt(AlphaDC,
		0,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		0,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));

	GdiAlphaBlend(hDC,
		400,
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

	/*if (m_iAlpha <= 0)
		m_bDead = true;*/
}

void CCurtain::Release(void)
{
}
