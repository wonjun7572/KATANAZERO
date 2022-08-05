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
		m_tRect.left + iScrollX,				// 복사 받을 위치의 좌표 전달(x,y 순서)
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,										// 복사 받을 이미지의 길이 전달(가로, 세로순서)
		(int)m_tInfo.fCY,
		hMemDC,												// 비트맵을 가지고 있는 dc	
		0,
		0,
		(int)m_tInfo.fCX,										// 복사 할 비트맵 의 가로, 세로 사이즈
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

	// fabs : 절대값을 구해주는 함수
	float	fWidth = fabs(pDest->Get_Info().fX - pSour->fX);
	float	fHeight = fabs(pDest->Get_Info().fY - pSour->fY);

	// sqrtf : 루트를 씌워 값을 구해주는 함수
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDest->Get_Info().fCX + pSour->fCX) * 0.5f;

	return fRadius >= fDiagonal;
}