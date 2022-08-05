#include "stdafx.h"
#include "Lazer.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "Player.h"

CLazer::CLazer()
{
}

CLazer::~CLazer()
{
	Release();
}

void CLazer::Initialize(void)
{
	m_tInfo = { 0,0, 3.f, 139.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/object/Laser.bmp", L"LASER");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/object/LaserShot.bmp", L"LASER_SHOT");
	
	m_pFrameKey = L"LASER";
	m_eRenderGroup = UI;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.dwFrameSpeed = 10;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CLazer::Update(void)
{
	if (!CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)->empty())
		m_pPlayer = CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)->front();
	
	RECT rt{};

	if (IntersectRect(&rt, &m_pPlayer->Get_Rect(), &m_tRect) && dynamic_cast<CPlayer*>(m_pPlayer)->Get_CurState() != ROLL)
	{
		m_pFrameKey = L"LASER_SHOT";
		CScrollMgr::Get_Instance()->Set_ScrollX(sinf((float)GetTickCount()) * 10);
		CScrollMgr::Get_Instance()->Set_ScrollY(cosf((float)GetTickCount()) * 10);
		dynamic_cast<CPlayer*>(m_pPlayer)->Set_Dead(true);
	}
	else if (IntersectRect(&rt, &m_pPlayer->Get_Rect(), &m_tRect))
	{
		m_pFrameKey = L"LASER_SHOT";
		CScrollMgr::Get_Instance()->Set_ScrollX(sinf((float)GetTickCount()) * 10);
		CScrollMgr::Get_Instance()->Set_ScrollY(cosf((float)GetTickCount()) * 10);
	}
	else
	{
		m_pFrameKey = L"LASER";
	}

	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CLazer::Late_Update(void)
{
}

void CLazer::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,					// 복사 받을 위치의 좌표 전달(x,y 순서)
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,							// 복사 받을 이미지의 길이 전달(가로, 세로순서)
		(int)m_tInfo.fCY,
		hMemDC,										// 비트맵을 가지고 있는 dc
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,	// 출력할 비트맵 시작 좌표(x,y 순서)
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,							// 복사 할 비트맵 의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));							// 제거할 픽셀의 색상
}

void CLazer::Release(void)
{
}