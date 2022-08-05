#include "stdafx.h"
#include "HitEffect.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "HitEffect_1.h"
#include "AbstractFactory.h"

CHitEffect::CHitEffect()
{
}


CHitEffect::~CHitEffect()
{
}

void CHitEffect::Initialize(void)
{
	m_tInfo = { 0.f, 0.f, 80.f, 79.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/effect/effect_blood_6x2.bmp", L"BLOOD_EFFECT_1");
	m_pFrameKey = L"BLOOD_EFFECT_1";
	m_eRenderGroup = BACKGROUND;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 6;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CHitEffect::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CHitEffect::Late_Update(void)
{
}

void CHitEffect::Render(HDC hDC)
{
	HDC hBloodDC = CBmpMgr::Get_Instance()->Find_Img(L"BLOOD_EFFECT_1");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_eDir == DIR_RIGHT)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,					// 복사 받을 위치의 좌표 전달(x,y 순서)
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,										// 복사 받을 이미지의 길이 전달(가로, 세로순서)
			(int)m_tInfo.fCY,
			hBloodDC,												// 비트맵을 가지고 있는 dc	
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,				// 출력할 비트맵 시작 좌표(x,y 순서)
			0,
			(int)m_tInfo.fCX,										// 복사 할 비트맵 의 가로, 세로 사이즈
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));										// 제거할 픽셀의 색상
	}
	else if(m_eDir == DIR_LEFT)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,				// 복사 받을 위치의 좌표 전달(x,y 순서)
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,										// 복사 받을 이미지의 길이 전달(가로, 세로순서)
			(int)m_tInfo.fCY,
			hBloodDC,												// 비트맵을 가지고 있는 dc	
			480 - ((int)m_tInfo.fCX * m_tFrame.iFrameStart),		// 1050 부터 0으로
			79,
			(int)m_tInfo.fCX,										// 복사 할 비트맵 의 가로, 세로 사이즈
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));										// 제거할 픽셀의 색상
	}

	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		m_bDead = true;
}

void CHitEffect::Release(void)
{
}
