#include "stdafx.h"
#include "ReflectEffect.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CReflectEffect::CReflectEffect()
{
}


CReflectEffect::~CReflectEffect()
{
}

void CReflectEffect::Initialize(void)
{
	m_tInfo = { 0.f, 0.f, 147.f, 140.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/effect/effect_reflect_6x2.bmp", L"REFLECT_EFFECT");
	m_pFrameKey = L"REFLECT_EFFECT";
	m_eRenderGroup = EFFECT;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CReflectEffect::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CReflectEffect::Late_Update(void)
{
}

void CReflectEffect::Render(HDC hDC)
{
	HDC hSparkDC = CBmpMgr::Get_Instance()->Find_Img(L"REFLECT_EFFECT");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_eDir == DIR_RIGHT)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,					// 복사 받을 위치의 좌표 전달(x,y 순서)
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,										// 복사 받을 이미지의 길이 전달(가로, 세로순서)
			(int)m_tInfo.fCY,
			hSparkDC,												// 비트맵을 가지고 있는 dc	
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,				// 출력할 비트맵 시작 좌표(x,y 순서)
			0,
			(int)m_tInfo.fCX,										// 복사 할 비트맵 의 가로, 세로 사이즈
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));										// 제거할 픽셀의 색상
	}
	else if (m_eDir == DIR_LEFT)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,				// 복사 받을 위치의 좌표 전달(x,y 순서)
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,										// 복사 받을 이미지의 길이 전달(가로, 세로순서)
			(int)m_tInfo.fCY,
			hSparkDC,												// 비트맵을 가지고 있는 dc	
			883 - ((int)m_tInfo.fCX * m_tFrame.iFrameStart),		// 1050 부터 0으로
			140,
			(int)m_tInfo.fCX,										// 복사 할 비트맵 의 가로, 세로 사이즈
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));										// 제거할 픽셀의 색상
	}


	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		m_bDead = true;
}

void CReflectEffect::Release(void)
{
}
