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
		m_tRect.left + iScrollX,					// ���� ���� ��ġ�� ��ǥ ����(x,y ����)
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,										// ���� ���� �̹����� ���� ����(����, ���μ���)
		(int)m_tInfo.fCY,
		hMemDC,										// ��Ʈ���� ������ �ִ� dc
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,	// ����� ��Ʈ�� ���� ��ǥ(x,y ����)
		0,
		(int)m_tInfo.fCX,							// ���� �� ��Ʈ�� �� ����, ���� ������
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));							// ������ �ȼ��� ����

	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		m_bDead = true;
}

void CAirLazer::Release(void)
{
}
