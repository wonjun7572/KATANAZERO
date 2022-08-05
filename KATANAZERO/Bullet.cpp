#include "stdafx.h"
#include "Bullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
}

void CBullet::Initialize(void)
{
	m_tInfo = { 0.f, 0.f, 48.f, 2.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/enemy/enemy_bullet.bmp", L"ENEMY_BULLET");
	m_pFrameKey = L"ENEMY_BULLET";
	m_eRenderGroup = GAMEOBJECT;
}

int CBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::Late_Update(void)
{
	if (m_eDir == DIR_LEFT)
	{
		m_tInfo.fX -= 25.f;
	}
	else if (m_eDir == DIR_RIGHT)
	{
		m_tInfo.fX += 25.f;
	}
	// no �Ѿ��� ���� �ٶ󺸰Բ� ��� �� ���Ŀ� ���� �׳༮������ ��� �Ѿ� �����ؾ���.
	// ���� �� ������ �Ʒ��� ��� �ϸ� �������� ƨ�ܳ��Բ�...?
}

void CBullet::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hDC,		
		m_tRect.left + iScrollX, 
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		0,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));
}

void CBullet::Release(void)
{
}
