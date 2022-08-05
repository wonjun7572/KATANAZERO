#include "stdafx.h"
#include "Bottle.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CBottle::CBottle()
{
}

CBottle::~CBottle()
{
}

void CBottle::Initialize(void)
{
	m_tInfo.fCX = 48.f;
	m_tInfo.fCY = 48.f;
	m_fSpeed = 30.f;

	m_fDiagonal = 20.f;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/object/bottle.bmp", L"BOTTLE_ITEM");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/object/bottle_reset.bmp", L"BOTTLE_ITEM_RESET");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/object/bottle_plg.bmp", L"BOTTLE_ITEM_PLG");
	m_pFrameKey = L"BOTTLE_ITEM";
	m_eRenderGroup = GAMEOBJECT;
}

int CBottle::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_tInfo.fX > 5000.f)
	{
		m_bDead = true;
	}
	else if (m_tInfo.fX < -100.f)
	{
		m_bDead = true;
	}
	else if (m_tInfo.fY < -100.f)
	{
		m_bDead = true;
	}
	else if (m_tInfo.fY > 1500.f)
	{
		m_bDead = true;
	}

	m_tInfo.fX -= cosf(m_fAngle * (PI / 180.f)) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * (PI / 180.f)) * m_fSpeed;

	float	fDiagonal = sqrtf((m_tInfo.fCX * 0.5f) * (m_tInfo.fCX * 0.5f) + (m_tInfo.fCY * 0.5f) * (m_tInfo.fCY * 0.5f));

	m_fRotAngle -= 60.f;

	// �� ���
	m_tPoint[0].x = long((m_tInfo.fCX * 0.5f) + fDiagonal * cosf((m_fRotAngle + 135.f) * (PI / 180.f)));
	m_tPoint[0].y = long((m_tInfo.fCY * 0.5f) - fDiagonal * sinf((m_fRotAngle + 135.f) * (PI / 180.f)));

	// �� ���
	m_tPoint[1].x = long((m_tInfo.fCX * 0.5f) + fDiagonal * cosf((m_fRotAngle + 45.f) * (PI / 180.f)));
	m_tPoint[1].y = long((m_tInfo.fCY * 0.5f) - fDiagonal * sinf((m_fRotAngle + 45.f) * (PI / 180.f)));

	// �� �ϴ�						
	m_tPoint[2].x = long((m_tInfo.fCX * 0.5f) + fDiagonal * cosf((m_fRotAngle + 225.f) * (PI / 180.f)));
	m_tPoint[2].y = long((m_tInfo.fCY * 0.5f) - fDiagonal * sinf((m_fRotAngle + 225.f) * (PI / 180.f)));

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBottle::Late_Update(void)
{
}

void CBottle::Render(HDC hDC)
{
	int	iScrollX = int(CScrollMgr::Get_Instance()->Get_ScrollX());
	int	iScrollY = int(CScrollMgr::Get_Instance()->Get_ScrollY());

	HDC hRotaionDC = CBmpMgr::Get_Instance()->Find_Img(L"BOTTLE_ITEM_PLG");
	HDC hResetDC = CBmpMgr::Get_Instance()->Find_Img(L"BOTTLE_ITEM_RESET");
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"BOTTLE_ITEM");

	PlgBlt(hRotaionDC, // ȸ�� ��ų �̹����� ��� �׸� ���ΰ�
		m_tPoint,	// �׸��� �׸� �簢���� ��ǥ  POINT ���� 3��, �迭�� ������ �� ���, �� ���, �� �ϴ� ��
		hMemDC,		// ��� �ִ� �̹����� �׸� ���ΰ�
		0,			// �׸� �̹��� X,Y ��ǥ
		0,
		(int)m_tInfo.fCX, // �̹��� ����, ���� ������
		(int)m_tInfo.fCY,
		NULL,
		NULL,
		NULL);

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,				// ���� ���� ��ġ�� ��ǥ ����(x,y ����)
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,										// ���� ���� �̹����� ���� ����(����, ���μ���)
		(int)m_tInfo.fCY,
		hRotaionDC,												// ��Ʈ���� ������ �ִ� dc	
		0,
		0,
		(int)m_tInfo.fCX,										// ���� �� ��Ʈ�� �� ����, ���� ������
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));

	BitBlt(hRotaionDC,
		0,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hResetDC,
		0,
		0,
		SRCCOPY);
}

void CBottle::Release(void)
{
}
