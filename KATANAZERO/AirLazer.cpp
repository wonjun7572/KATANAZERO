#include "stdafx.h"
#include "AirLazer.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CAirLazer::CAirLazer()
{
}


CAirLazer::~CAirLazer()
{
}

void CAirLazer::Initialize(void)
{
	m_tInfo = { 0.f,0.f,36.f,1500.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/boss/boss_lazer_top_10x1.bmp", L"BOSS_LAZER_AIR");
	m_pFrameKey = L"BOSS_LAZER_AIR";
	m_eRenderGroup = EFFECT;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 10;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CAirLazer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CAirLazer::Late_Update(void)
{
}

void CAirLazer::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"BOSS_LAZER_AIR");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,					// 복사 받을 위치의 좌표 전달(x,y 순서)
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,										// 복사 받을 이미지의 길이 전달(가로, 세로순서)
		(int)m_tInfo.fCY,
		hMemDC,										// 비트맵을 가지고 있는 dc
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,	// 출력할 비트맵 시작 좌표(x,y 순서)
		0,
		(int)m_tInfo.fCX,							// 복사 할 비트맵 의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));							// 제거할 픽셀의 색상

	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		m_bDead = true;
}

void CAirLazer::Release(void)
{
}
