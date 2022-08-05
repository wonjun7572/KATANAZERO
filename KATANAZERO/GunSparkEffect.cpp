#include "stdafx.h"
#include "GunSparkEffect.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CGunSparkEffect::CGunSparkEffect()
{
}


CGunSparkEffect::~CGunSparkEffect()
{
}

void CGunSparkEffect::Initialize(void)
{
	m_tInfo = { 0.f, 0.f, 83.f, 78.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/effect/effect_gunspark_4x2.bmp", L"GUN_SPARK_EFFECT");
	m_pFrameKey = L"GUN_SPARK_EFFECT";
	m_eRenderGroup = EFFECT;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CGunSparkEffect::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CGunSparkEffect::Late_Update(void)
{
}

void CGunSparkEffect::Render(HDC hDC)
{
	HDC hSparkDC = CBmpMgr::Get_Instance()->Find_Img(L"GUN_SPARK_EFFECT");

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
			392 - ((int)m_tInfo.fCX * m_tFrame.iFrameStart),		// 1050 부터 0으로
			78,
			(int)m_tInfo.fCX,										// 복사 할 비트맵 의 가로, 세로 사이즈
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));										// 제거할 픽셀의 색상
	}


	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		m_bDead = true;
}

void CGunSparkEffect::Release(void)
{
}
