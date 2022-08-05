#include "stdafx.h"
#include "Door.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CDoor::CDoor()
{
	ZeroMemory(&m_renderInfo, sizeof(m_renderInfo));
	ZeroMemory(&m_renderRect, sizeof(m_renderRect));
}

CDoor::~CDoor()
{
}

void CDoor::Initialize(void)
{
	m_tInfo = {0,0, 50.f, 130.f};
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/object/Door_Sheet.bmp", L"DOOR_SHEET");
	m_pFrameKey = L"DOOR_SHEET";
	m_eRenderGroup = HIT_EFFECT;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 19;
	m_tFrame.dwFrameSpeed = 100;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CDoor::Update(void)
{
	if (m_bDead)
		m_bDooropen = true;

	if (m_bDooropen && m_tFrame.iFrameStart < 3)
	{
		m_bDooropen = !m_bDooropen;
		m_bOpened = true;
	}

	if (m_bOpened && m_tFrame.iFrameStart <= m_tFrame.iFrameEnd)
		Move_Frame();

	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		m_bOpened = false;

	m_renderInfo = { m_tInfo.fX + 40, m_tInfo.fY, 163.f, 130.f};
	InfoToRect();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CDoor::Late_Update(void)
{

}

void CDoor::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hDC,
		m_renderRect.left + iScrollX,					// ���� ���� ��ġ�� ��ǥ ����(x,y ����)
		m_renderRect.top + iScrollY,
		(int)m_renderInfo.fCX,							// ���� ���� �̹����� ���� ����(����, ���μ���)
		(int)m_renderInfo.fCY,
		hMemDC,										// ��Ʈ���� ������ �ִ� dc
		(int)m_renderInfo.fCX * m_tFrame.iFrameStart,	// ����� ��Ʈ�� ���� ��ǥ(x,y ����)
		(int)m_renderInfo.fCY * m_tFrame.iMotion,
		(int)m_renderInfo.fCX,							// ���� �� ��Ʈ�� �� ����, ���� ������
		(int)m_renderInfo.fCY,
		RGB(255, 0, 255));							// ������ �ȼ��� ����
}

void CDoor::Release(void)
{
}

void CDoor::InfoToRect()
{
	m_renderRect.left = LONG(m_renderInfo.fX - (m_renderInfo.fCX * 0.5f));
	m_renderRect.top = LONG(m_renderInfo.fY - (m_renderInfo.fCY * 0.5f));
	m_renderRect.right = LONG(m_renderInfo.fX + (m_renderInfo.fCX * 0.5f));
	m_renderRect.bottom = LONG(m_renderInfo.fY + (m_renderInfo.fCY * 0.5f));
}