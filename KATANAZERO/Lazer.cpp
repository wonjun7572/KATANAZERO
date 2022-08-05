#include "stdafx.h"
#include "Lazer.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "Player.h"

CLazer::CLazer()
{
}

CLazer::~CLazer()
{
	Release();
}

void CLazer::Initialize(void)
{
	m_tInfo = { 0,0, 3.f, 139.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/object/Laser.bmp", L"LASER");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/object/LaserShot.bmp", L"LASER_SHOT");
	
	m_pFrameKey = L"LASER";
	m_eRenderGroup = UI;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.dwFrameSpeed = 10;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CLazer::Update(void)
{
	if (!CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)->empty())
		m_pPlayer = CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)->front();
	
	RECT rt{};

	if (IntersectRect(&rt, &m_pPlayer->Get_Rect(), &m_tRect) && dynamic_cast<CPlayer*>(m_pPlayer)->Get_CurState() != ROLL)
	{
		m_pFrameKey = L"LASER_SHOT";
		CScrollMgr::Get_Instance()->Set_ScrollX(sinf((float)GetTickCount()) * 10);
		CScrollMgr::Get_Instance()->Set_ScrollY(cosf((float)GetTickCount()) * 10);
		dynamic_cast<CPlayer*>(m_pPlayer)->Set_Dead(true);
	}
	else if (IntersectRect(&rt, &m_pPlayer->Get_Rect(), &m_tRect))
	{
		m_pFrameKey = L"LASER_SHOT";
		CScrollMgr::Get_Instance()->Set_ScrollX(sinf((float)GetTickCount()) * 10);
		CScrollMgr::Get_Instance()->Set_ScrollY(cosf((float)GetTickCount()) * 10);
	}
	else
	{
		m_pFrameKey = L"LASER";
	}

	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CLazer::Late_Update(void)
{
}

void CLazer::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,					// ���� ���� ��ġ�� ��ǥ ����(x,y ����)
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,							// ���� ���� �̹����� ���� ����(����, ���μ���)
		(int)m_tInfo.fCY,
		hMemDC,										// ��Ʈ���� ������ �ִ� dc
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,	// ����� ��Ʈ�� ���� ��ǥ(x,y ����)
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,							// ���� �� ��Ʈ�� �� ����, ���� ������
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));							// ������ �ȼ��� ����
}

void CLazer::Release(void)
{
}