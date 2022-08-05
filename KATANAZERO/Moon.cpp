#include "stdafx.h"
#include "Moon.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "Boss.h"

CMoon::CMoon()
{
}

CMoon::~CMoon()
{
}

void CMoon::Initialize(void)
{
	m_tInfo = { 0.f, 0.f, 1000.f, 700.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/API.bmp", L"MOON");
	m_pFrameKey = L"MOON";
	m_eRenderGroup = HIT_EFFECT;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 9;
	m_tFrame.dwFrameSpeed = 400;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CMoon::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOSS)->empty())
	{
		if(dynamic_cast<CBoss*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOSS)->front())->Get_RealDead() == true)
		Move_Frame();
	}

	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		m_bFinished = true;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMoon::Late_Update(void)
{
}

void CMoon::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	if (m_bFinished)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,	// ���� ���� ��ġ�� ��ǥ ����(x,y ����)
			m_tRect.top + iScrollY,
			(int)m_tInfo.fCX,			// ���� ���� �̹����� ���� ����(����, ���μ���)
			(int)m_tInfo.fCY,
			hMemDC,						// ��Ʈ���� ������ �ִ� dc
			(int)m_tInfo.fCX * m_tFrame.iFrameEnd, 	// ����� ��Ʈ�� ���� ��ǥ(x,y ����)
			0,
			(int)m_tInfo.fCX,			// ���� �� ��Ʈ�� �� ����, ���� ������
			(int)m_tInfo.fCY,
			RGB(31, 31, 31));			// ������ �ȼ��� ����
	}
	else
	{
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
			RGB(31, 31, 31));			// ������ �ȼ��� ����
	}
}

void CMoon::Release(void)
{
	if (m_pGraphics)
		delete m_pGraphics;
	if (m_pTexture)
		delete m_pTexture;
}
