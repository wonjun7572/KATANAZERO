#include "stdafx.h"
#include "GroundLazer.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CGroundLazer::CGroundLazer()
{
}


CGroundLazer::~CGroundLazer()
{
}

void CGroundLazer::Initialize(void)
{
	m_tInfo = { 0.f,0.f,1500.f,36.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/boss/boss_lazer_ground_1x10.bmp", L"BOSS_LAZER_GROUND");
	m_pFrameKey = L"BOSS_LAZER_GROUND";
	m_eRenderGroup = EFFECT;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 10;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CGroundLazer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CGroundLazer::Late_Update(void)
{
}

void CGroundLazer::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"BOSS_LAZER_GROUND");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,					// ���� ���� ��ġ�� ��ǥ ����(x,y ����)
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,										// ���� ���� �̹����� ���� ����(����, ���μ���)
		(int)m_tInfo.fCY,
		hMemDC,										// ��Ʈ���� ������ �ִ� dc
		0,	// ����� ��Ʈ�� ���� ��ǥ(x,y ����)
		(int)m_tInfo.fCY * m_tFrame.iFrameStart,
		(int)m_tInfo.fCX,							// ���� �� ��Ʈ�� �� ����, ���� ������
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));							// ������ �ȼ��� ����

	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		m_bDead = true;
}

void CGroundLazer::Release(void)
{
}
