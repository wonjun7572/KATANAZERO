#include "stdafx.h"
#include "HitEffect_1.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CHitEffect_1::CHitEffect_1()
{
}


CHitEffect_1::~CHitEffect_1()
{
}

void CHitEffect_1::Initialize(void)
{
	m_tInfo = { 0.f, 0.f, 128.f, 123.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/effect/effect_blood_remain3_L.bmp", L"BLOOD_REMAIN_3_L");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/effect/effect_blood_remain3_R.bmp", L"BLOOD_REMAIN_3_R");
	m_eRenderGroup = BACKGROUND;
}

int CHitEffect_1::Update(void)
{
	if (m_bDead)
		return OBJ_NOEVENT;

	if (m_eDir == DIR_LEFT)
	{
		m_pFrameKey = L"BLOOD_REMAIN_3_L";
	}
	else if (m_eDir == DIR_RIGHT)
	{
		m_pFrameKey = L"BLOOD_REMAIN_3_R";
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CHitEffect_1::Late_Update(void)
{

}

void CHitEffect_1::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,	// 복사 받을 위치의 좌표 전달(x,y 순서)
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,			// 복사 받을 이미지의 길이 전달(가로, 세로순서)
		(int)m_tInfo.fCY,
		hMemDC,						// 비트맵을 가지고 있는 dc
		0, 							// 출력할 비트맵 시작 좌표(x,y 순서)
		0,
		(int)m_tInfo.fCX,			// 복사 할 비트맵 의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));			// 제거할 픽셀의 색상
}

void CHitEffect_1::Release(void)
{
}
