#include "stdafx.h"
#include "SmokeGas.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "Player.h"

CSmokeGas::CSmokeGas()
{
}

CSmokeGas::~CSmokeGas()
{
}

void CSmokeGas::Initialize(void)
{
	m_tInfo.fCX = 56.f;
	m_tInfo.fCY = 56.f;
	m_fSpeed = 30.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/object/smoke_gas_1.bmp", L"SMOKE_GAS_ITEM_1");
	m_eRenderGroup = EFFECT;

	m_pFrameKey = L"SMOKE_GAS_ITEM_1";
	m_BlendFunction.BlendOp = AC_SRC_OVER;
	m_BlendFunction.BlendFlags = 0;
	m_BlendFunction.AlphaFormat = 0;
	m_iAlpha = 255;
}

int CSmokeGas::Update(void)
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

void CSmokeGas::Late_Update(void)
{
}

void CSmokeGas::Render(HDC hDC)
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
		RGB(31, 31, 31));

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
		RGB(31, 31, 31));

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

void CSmokeGas::Release(void)
{
}

bool CSmokeGas::Check_Sphere(CObj* pDest, INFO* pSour)
{
	// c^2 = a^2 + b^2

	// fabs : 절대값을 구해주는 함수
	float	fWidth = fabs(pDest->Get_Info().fX - pSour->fX);
	float	fHeight = fabs(pDest->Get_Info().fY - pSour->fY);

	// sqrtf : 루트를 씌워 값을 구해주는 함수
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDest->Get_Info().fCX + pSour->fCX) * 0.5f;

	return fRadius >= fDiagonal;
}