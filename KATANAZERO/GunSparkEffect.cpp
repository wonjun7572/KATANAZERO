#include "stdafx.h"
#include "GunSparkEffect.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CGunSparkEffect::CGunSparkEffect()
{
}


CGunSparkEffect::~CGunSparkEffect()
{
}

void CGunSparkEffect::Initialize(void)
{
	m_tInfo = { 0.f, 0.f, 83.f, 78.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/effect/effect_gunspark_4x2.bmp", L"GUN_SPARK_EFFECT");
	m_pFrameKey = L"GUN_SPARK_EFFECT";
	m_eRenderGroup = EFFECT;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CGunSparkEffect::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CGunSparkEffect::Late_Update(void)
{
}

void CGunSparkEffect::Render(HDC hDC)
{
	HDC hSparkDC = CBmpMgr::Get_Instance()->Find_Img(L"GUN_SPARK_EFFECT");

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
			392 - ((int)m_tInfo.fCX * m_tFrame.iFrameStart),		// 1050 ���� 0����
			78,
			(int)m_tInfo.fCX,										// ���� �� ��Ʈ�� �� ����, ���� ������
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));										// ������ �ȼ��� ����
	}


	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		m_bDead = true;
}

void CGunSparkEffect::Release(void)
{
}
