#include "stdafx.h"
#include "BottelUI.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "Player.h"

CBottelUI::CBottelUI()
{
}


CBottelUI::~CBottelUI()
{
	Release();
}

void CBottelUI::Initialize(void)
{
	m_tInfo = { 0.f, 0.f, 48.f, 48.f };
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../image/object/bottle.bmp", L"BOTTLE_ITEM");
	m_pFrameKey = L"BOTTLE_ITEM";
	m_eRenderGroup = UI;
	m_iID = 2;
}

int CBottelUI::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)->empty())
		m_pPlayer = CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER)->front();

	if (Check_Sphere(m_pPlayer, &m_tInfo) && dynamic_cast<CPlayer*>(m_pPlayer)->Get_Item() == false)
	{
		m_bItem = true;
	}

	if (m_bItem == true)
	{
		m_tInfo.fX = m_pPlayer->Get_Info().fX;
		m_tInfo.fY = m_pPlayer->Get_Info().fY - 50.f;
		dynamic_cast<CPlayer*>(m_pPlayer)->Set_Item(true);
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CBottelUI::Late_Update(void)
{
}

void CBottelUI::Render(HDC hDC)
{
	int	iScrollX = int(CScrollMgr::Get_Instance()->Get_ScrollX());
	int	iScrollY = int(CScrollMgr::Get_Instance()->Get_ScrollY());

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,				// ���� ���� ��ġ�� ��ǥ ����(x,y ����)
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,										// ���� ���� �̹����� ���� ����(����, ���μ���)
		(int)m_tInfo.fCY,
		hMemDC,												// ��Ʈ���� ������ �ִ� dc	
		0,
		0,
		(int)m_tInfo.fCX,										// ���� �� ��Ʈ�� �� ����, ���� ������
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));

	if (m_bItem == true)
	{
		GdiTransparentBlt(hDC,
			1170,
			5,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hMemDC,
			0,
			0,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	}
}

void CBottelUI::Release(void)
{
}

bool CBottelUI::Check_Sphere(CObj * pDest, INFO * pSour)
{
	// c^2 = a^2 + b^2

	// fabs : ���밪�� �����ִ� �Լ�
	float	fWidth = fabs(pDest->Get_Info().fX - pSour->fX);
	float	fHeight = fabs(pDest->Get_Info().fY - pSour->fY);

	// sqrtf : ��Ʈ�� ���� ���� �����ִ� �Լ�
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDest->Get_Info().fCX + pSour->fCX) * 0.5f;

	return fRadius >= fDiagonal;
}