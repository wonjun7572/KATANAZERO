#include "stdafx.h"
#include "Line.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"


CLine::CLine()
{
	ZeroMemory(&m_tInfo, sizeof(LINE));
}

CLine::CLine(LINEPOINT & tLeftPt, LINEPOINT& tRightPt)
	: m_tInfo(tLeftPt, tRightPt)
{
}

CLine::CLine(LINE& rLine)
	: m_tInfo(rLine)
{

}

CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScroolY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	MoveToEx(hDC, (int)m_tInfo.tLeftPt.fX + iScrollX, (int)m_tInfo.tLeftPt.fY + iScroolY, nullptr);

	LineTo(hDC, (int)m_tInfo.tRightPt.fX + iScrollX, (int)m_tInfo.tRightPt.fY + iScroolY);
}
