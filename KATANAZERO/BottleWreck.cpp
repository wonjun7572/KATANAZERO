#include "stdafx.h"
#include "BottleWreck.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "LineMgr.h"

CBottleWreck::CBottleWreck()
{
}

CBottleWreck::~CBottleWreck()
{
}

void CBottleWreck::Initialize(void)
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 14.f;
	m_fSpeed = 30.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/object/bottle_wreck_1.bmp", L"BOTTLE_WRECK_ITEM_1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/object/bottle_wreck_2.bmp", L"BOTTLE_WRECK_ITEM_2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/object/bottle_wreck_3.bmp", L"BOTTLE_WRECK_ITEM_3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/object/bottle_wreck_4.bmp", L"BOTTLE_WRECK_ITEM_4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/object/bottle_wreck_5.bmp", L"BOTTLE_WRECK_ITEM_5");
	m_eRenderGroup = GAMEOBJECT;
}

int CBottleWreck::Update(void)
{

	Graviting();
	Update_Rect();
	return 0;
}

void CBottleWreck::Late_Update(void)
{
}

void CBottleWreck::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"BOTTLE_WRECK_ITEM_3");
	int	iScrollX = int(CScrollMgr::Get_Instance()->Get_ScrollX());
	int	iScrollY = int(CScrollMgr::Get_Instance()->Get_ScrollY());

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,				// 복사 받을 위치의 좌표 전달(x,y 순서)
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,										// 복사 받을 이미지의 길이 전달(가로, 세로순서)
		(int)m_tInfo.fCY,
		hMemDC,												// 비트맵을 가지고 있는 dc	
		0,
		0,
		(int)m_tInfo.fCX,										// 복사 할 비트맵 의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));
}


void CBottleWreck::Graviting(void)
{
	float	fX = m_tInfo.fX;
	float	fY = 0;

	m_bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);

	if (m_bJump)
	{
		if (GetTickCount() % 2 ==0)
		{
			m_fPlusX = (float)(GetTickCount() % 15);
			m_tInfo.fX += m_fPlusX;
			m_tInfo.fY -= m_fJumpPower * m_fJumpTime - (9.8f * m_fJumpTime * m_fJumpTime) * 0.5f;
		}
		else if (GetTickCount() % 2 == 1)
		{
			m_fPlusX = (float)(GetTickCount() % 15);
			m_tInfo.fX -= m_fPlusX;
			m_tInfo.fY -= m_fJumpPower * m_fJumpTime - (9.8f * m_fJumpTime * m_fJumpTime) * 0.5f;
		}

		m_fJumpTime += 0.2f;

		if (m_bLineCol && (fY < m_tInfo.fY))
		{
			m_bJump = false;
			m_fJumpTime = 0.f;
			m_tInfo.fY = fY;
		}
	}
	else if (m_bLineCol)
	{
		m_tInfo.fY = fY - m_tInfo.fCY * 0.5f;

	}
	else
	{
		m_tInfo.fY -= 5.f;
	}
}

void CBottleWreck::Release(void)
{
}
