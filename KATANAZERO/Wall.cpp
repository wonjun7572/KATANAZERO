#include "stdafx.h"
#include "Wall.h"
#include "ScrollMgr.h"

CWall::CWall()
{
}

CWall::CWall(INFO _info)
{
	m_tInfo = _info;
	m_eRenderGroup = BACKGROUND;
}

CWall::~CWall()
{
	Release();
}

void CWall::Initialize(void)
{
	m_eRenderGroup = BACKGROUND;
}

int CWall::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CWall::Late_Update(void)
{
}

void CWall::Render(HDC hDC)
{
	//int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	//Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
}

void CWall::Release(void)
{
}