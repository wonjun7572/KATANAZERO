#include "stdafx.h"
#include "Knife.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CKnife::CKnife()
{
}

CKnife::~CKnife()
{
	Release();
}

void CKnife::Initialize(void)
{
	m_tInfo.fCX = 42.f;
	m_tInfo.fCY = 42.f;
	m_fSpeed = 30.f;

	m_fDiagonal = 20.f;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/object/knife.bmp", L"KNIFE_ITEM");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/object/knife_reset.bmp", L"KNIFE_ITEM_RESET");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/object/knife_plg.bmp", L"KNIFE_ITEM_PLG");
	m_pFrameKey = L"KNIFE_ITEM";
	m_eRenderGroup = GAMEOBJECT;
}

int CKnife::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_tInfo.fX > 5000.f)
	{
		m_bDead = true;
	}
	else if(m_tInfo.fX < -100.f)
	{
		m_bDead = true;
	}
	else if (m_tInfo.fY < -100.f)
	{
		m_bDead = true;
	}
	else if (m_tInfo.fY > 1500.f)
	{
		m_bDead = true;
	}

	m_tInfo.fX -= cosf(m_fAngle * (PI / 180.f)) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * (PI / 180.f)) * m_fSpeed;

	float	fDiagonal = sqrtf((m_tInfo.fCX * 0.5f) * (m_tInfo.fCX * 0.5f) + (m_tInfo.fCY * 0.5f) * (m_tInfo.fCY * 0.5f));

	m_fRotAngle -= 60.f;

	// 좌 상단
	m_tPoint[0].x = long((m_tInfo.fCX * 0.5f) + fDiagonal * cosf((m_fRotAngle + 135.f) * (PI / 180.f)));
	m_tPoint[0].y = long((m_tInfo.fCY * 0.5f) - fDiagonal * sinf((m_fRotAngle + 135.f) * (PI / 180.f)));

	// 우 상단
	m_tPoint[1].x = long((m_tInfo.fCX * 0.5f) + fDiagonal * cosf((m_fRotAngle + 45.f) * (PI / 180.f)));
	m_tPoint[1].y = long((m_tInfo.fCY * 0.5f) - fDiagonal * sinf((m_fRotAngle + 45.f) * (PI / 180.f)));

	// 좌 하단						
	m_tPoint[2].x = long((m_tInfo.fCX * 0.5f) + fDiagonal * cosf((m_fRotAngle + 225.f) * (PI / 180.f)));
	m_tPoint[2].y = long((m_tInfo.fCY * 0.5f) - fDiagonal * sinf((m_fRotAngle + 225.f) * (PI / 180.f)));

	Update_Rect();

	return OBJ_NOEVENT;
}

void CKnife::Late_Update(void)
{
}

void CKnife::Render(HDC hDC)
{
	int	iScrollX = int(CScrollMgr::Get_Instance()->Get_ScrollX());
	int	iScrollY = int(CScrollMgr::Get_Instance()->Get_ScrollY());

	HDC hRotaionDC = CBmpMgr::Get_Instance()->Find_Img(L"KNIFE_ITEM_PLG");
	HDC hResetDC = CBmpMgr::Get_Instance()->Find_Img(L"KNIFE_ITEM_RESET");
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"KNIFE_ITEM");

	PlgBlt(hRotaionDC, // 회전 시킬 이미지를 어디에 그릴 것인가
		m_tPoint,	// 그림을 그릴 사각형의 좌표  POINT 변수 3개, 배열의 순서는 좌 상단, 우 상단, 좌 하단 순
		hMemDC,		// 어디에 있는 이미지를 그릴 것인가
		0,			// 그릴 이미지 X,Y 좌표
		0,
		(int)m_tInfo.fCX, // 이미지 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		NULL,
		NULL,
		NULL);

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,				// 복사 받을 위치의 좌표 전달(x,y 순서)
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,										// 복사 받을 이미지의 길이 전달(가로, 세로순서)
		(int)m_tInfo.fCY,
		hRotaionDC,												// 비트맵을 가지고 있는 dc	
		0,
		0,
		(int)m_tInfo.fCX,										// 복사 할 비트맵 의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));

	BitBlt(hRotaionDC,
		0,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hResetDC,
		0,
		0,
		SRCCOPY);
}

void CKnife::Release(void)
{
}
