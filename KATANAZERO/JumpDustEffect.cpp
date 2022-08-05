#include "stdafx.h"
#include "JumpDustEffect.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CJumpDustEffect::CJumpDustEffect()
{
}


CJumpDustEffect::~CJumpDustEffect()
{
}

void CJumpDustEffect::Initialize(void)
{
	m_tInfo = { 0.f, 0.f, 42.f, 80.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/player/player_jumpdust_5x1.bmp", L"PLAYER_JUMPDUST_EFFECT");
	m_pFrameKey = L"PLAYER_JUMPDUST_EFFECT";
	m_eRenderGroup = EFFECT;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CJumpDustEffect::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CJumpDustEffect::Late_Update(void)
{
}

void CJumpDustEffect::Render(HDC hDC)
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
		(int)m_tInfo.fCX * m_tFrame.iFrameStart, 	// 출력할 비트맵 시작 좌표(x,y 순서)
		0,
		(int)m_tInfo.fCX,			// 복사 할 비트맵 의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));			// 제거할 픽셀의 색상

	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		m_bDead = true;
}

void CJumpDustEffect::Release(void)
{
}
