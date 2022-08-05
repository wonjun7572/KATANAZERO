#include "stdafx.h"
#include "Explosion.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CExplosion::CExplosion()
{
}

CExplosion::~CExplosion()
{
}

void CExplosion::Initialize(void)
{
	m_tInfo = { 0.f, 0.f, 96.f, 112.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/effect/explosion.bmp", L"EXPLOSION_EFFECT");
	m_pFrameKey = L"EXPLOSION_EFFECT";
	m_eRenderGroup = EFFECT;
	m_tFrame.iFrameStart = 1;
	m_tFrame.iFrameEnd = 10;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CExplosion::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CExplosion::Late_Update(void)
{
}

void CExplosion::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,	// ���� ���� ��ġ�� ��ǥ ����(x,y ����)
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,			// ���� ���� �̹����� ���� ����(����, ���μ���)
		(int)m_tInfo.fCY,
		hMemDC,						// ��Ʈ���� ������ �ִ� dc
		(int)m_tInfo.fCX * m_tFrame.iFrameStart, 	// ����� ��Ʈ�� ���� ��ǥ(x,y ����)
		0,
		(int)m_tInfo.fCX,			// ���� �� ��Ʈ�� �� ����, ���� ������
		(int)m_tInfo.fCY,
		RGB(0, 0, 0));			// ������ �ȼ��� ����

	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		m_bDead = true;
}

void CExplosion::Release(void)
{
}
