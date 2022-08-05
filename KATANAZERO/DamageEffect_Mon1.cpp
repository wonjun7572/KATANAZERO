#include "stdafx.h"
#include "DamageEffect_Mon1.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CDamageEffect_Mon1::CDamageEffect_Mon1()
{
}

CDamageEffect_Mon1::~CDamageEffect_Mon1()
{
}

void CDamageEffect_Mon1::Initialize(void)
{
	m_tInfo = { 0.f, 0.f, 120.f, 74.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/enemy/enemy_grunt_slash_5x2.bmp", L"SWORD_MONSTER_EFFECT");
	m_pFrameKey = L"SWORD_MONSTER_EFFECT";
	m_eRenderGroup = EFFECT;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.dwFrameSpeed = 75;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CDamageEffect_Mon1::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CDamageEffect_Mon1::Late_Update(void)
{
}

void CDamageEffect_Mon1::Render(HDC hDC)
{
	HDC hSparkDC = CBmpMgr::Get_Instance()->Find_Img(L"SWORD_MONSTER_EFFECT");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_eDir == DIR_RIGHT)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,					// ���� ���� ��ġ�� ��ǥ ����(x,y ����)
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,										// ���� ���� �̹����� ���� ����(����, ���μ���)
			(int)m_tInfo.fCY,
			hSparkDC,												// ��Ʈ���� ������ �ִ� dc	
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,				// ����� ��Ʈ�� ���� ��ǥ(x,y ����)
			0,
			(int)m_tInfo.fCX,										// ���� �� ��Ʈ�� �� ����, ���� ������
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));										// ������ �ȼ��� ����
	}
	else if (m_eDir == DIR_LEFT)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,				// ���� ���� ��ġ�� ��ǥ ����(x,y ����)
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,										// ���� ���� �̹����� ���� ����(����, ���μ���)
			(int)m_tInfo.fCY,
			hSparkDC,												// ��Ʈ���� ������ �ִ� dc	
			600 - ((int)m_tInfo.fCX * m_tFrame.iFrameStart),		// 1050 ���� 0����
			74,
			(int)m_tInfo.fCX,										// ���� �� ��Ʈ�� �� ����, ���� ������
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));										// ������ �ȼ��� ����
	}


	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		m_bDead = true;
}

void CDamageEffect_Mon1::Release(void)
{
}
